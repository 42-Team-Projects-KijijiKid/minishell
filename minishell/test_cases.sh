#!/usr/bin/env bash
# quote_tests.sh — Exercise Bash quoting edge cases with colored pass/fail output.
# -------- Colors --------
RED=$'\e[31m'
GREEN=$'\e[32m'
YELLOW=$'\e[33m'
BLUE=$'\e[34m'
BOLD=$'\e[1m'
DIM=$'\e[2m'
RESET=$'\e[0m'
pass() { printf "%s✓ PASS%s\n" "$GREEN" "$RESET"; }
fail() { printf "%s✗ FAIL%s\n" "$RED" "$RESET"; }
sep()  { printf "%s—%s\n" "$DIM" "$RESET"; }
# -------- Runner --------
run_test() {
  local name="$1" cmd="$2" expected="$3" expected_status="${4:-0}"
  printf "%s%s%s\n" "$BOLD" "$name" "$RESET"
  printf "%s$ %s%s\n" "$BLUE" "$cmd" "$RESET"
  # Run in a clean subshell so per-test env tweaks don’t leak.
  local actual status
  actual="$(
    bash -c "$cmd" 2>&1
  )"
  status=$?
  # Compare status first
  if [[ "$status" -ne "$expected_status" ]]; then
    fail
    printf "%sExpected exit:%s %d  %sActual:%s %d\n" "$YELLOW" "$RESET" "$expected_status" "$YELLOW" "$RESET" "$status"
    printf "%s(Showing captured stdout+stderr below)%s\n" "$DIM" "$RESET"
    sep
    printf "%s\n" "$actual"
    sep
    return
  fi
  # Compare output (exact, byte-for-byte)
  if [[ "$actual" == "$expected" ]]; then
    pass
  else
    fail
    printf "%sExpected output:%s\n" "$YELLOW" "$RESET"
    sep
    printf "%s\n" "$expected"
    sep
    printf "%sActual output:%s\n" "$YELLOW" "$RESET"
    sep
    printf "%s\n" "$actual"
    sep
    # Lightweight inline diff (no external diff needed)
    printf "%sMini diff (– expected | + actual):%s\n" "$YELLOW" "$RESET"
    sep
    # Print per-line diff
    # shellcheck disable=SC2001
    {
      IFS=$'\n'
      # read into arrays line-by-line
      mapfile -t exp_lines <<<"$expected"
      mapfile -t act_lines <<<"$actual"
      local i max len_exp=${#exp_lines[@]} len_act=${#act_lines[@]}
      (( max = len_exp > len_act ? len_exp : len_act ))
      for (( i=0; i<max; i++ )); do
        [[ $i -lt $len_exp ]] && printf "%s- %s%s\n" "$DIM" "${exp_lines[i]}" "$RESET"
        [[ $i -lt $len_act ]] && printf "%s+ %s%s\n" "$DIM" "${act_lines[i]}" "$RESET"
      done
    }
    sep
  fi
}
# -------- Prepare a sandbox for deterministic globbing tests --------
SANDBOX="$(mktemp -d)"
cleanup() { rm -rf "$SANDBOX"; }
trap cleanup EXIT
(
  cd "$SANDBOX" || exit 1
  : > "abc"
  : > "abx"
  : > "a space.txt"
)
# -------- Tests --------
# 1) Single quotes: no expansions at all
run_test \
  "Single quotes prevent all expansions" \
  "echo '\$HOME * ? \$(echo hi)'" \
  '$HOME * ? $(echo hi)'
# 2) Double quotes: parameter + command substitution expand; glob chars are literal
run_test \
  "Double quotes expand \$, \$() but keep * and ? literal" \
  "HOME=/h echo \"\$HOME * ? \$(printf hi)\"" \
  "/h * ? hi"
# 3) Unquoted var: word splitting happens on spaces
run_test \
  "Unquoted variable splits on IFS spaces" \
  "v='a b'; printf '[%s]\n' \$v" \
  "[a]
[b]"
# 4) Quoted var: no word splitting
run_test \
  "Double-quoted variable preserves spaces" \
  "v='a b'; printf '[%s]\n' \"\$v\"" \
  "[a b]"
# 5) Globbing vs quoted globbing (deterministic in sandbox)
run_test \
  "Globbing expands unquoted *" \
  "cd '$SANDBOX'; printf '%s ' a*; echo" \
  "abc abx "
run_test \
  "Quoted * is literal" \
  "cd '$SANDBOX'; printf '%s\n' \"a*\"" \
  "a*"
# 6) Escaping a single quote inside single quotes (close, escape, reopen)
run_test \
  "Embed single quote using '\'' pattern" \
  "printf '%s\n' 'It'\''s fine'" \
  "It's fine"
# 7) ANSI C quoting $'...' interprets backslash escapes
run_test \
  "ANSI C quoting produces newlines and hex" \
  "printf '%s' \$'A\\nB * \\x2a'" \
  "A
B * *"
# 8) Here-doc: quoted delimiter disables expansion; unquoted enables it
run_test \
  "Here-doc with quoted delimiter (no expansion)" \
  $'HOME=/h bash -c \'cat <<\\EOF\n$HOME\n*\n$(echo hi)\nEOF\'' \
  '$HOME
*
$(echo hi)'
run_test \
  "Here-doc with unquoted delimiter (expansion and no globbing unless unquoted)" \
  $'HOME=/h bash -c \'cat <<EOF\n$HOME\n*\n$(echo hi)\nEOF\'' \
  "/h
*
hi"
# 9) Arrays: ${arr[@]} vs ${arr[*]} with and without quotes
run_test \
  'Array expansion: "${arr[@]}" preserves elements' \
  "arr=('a b' c); for x in \"\${arr[@]}\"; do printf '<%s>' \"\$x\"; done; echo" \
  "<a b><c>"
run_test \
  'Array expansion: "${arr[*]}" joins into one word' \
  "arr=('a b' c); printf '<%s>' \"\${arr[*]}\"; echo" \
  "<a b c>"
run_test \
  'Array expansion: ${arr[@]} (unquoted) splits elements' \
  "arr=('a b' c); for x in \${arr[@]}; do printf '<%s>' \"\$x\"; done; echo" \
  "<a><b><c>"
# 10) Trailing backslash outside quotes escapes newline (line continuation)
run_test \
  "Trailing backslash joins lines (no newline produced)" \
  "printf '%s' Hel\\
lo" \
  "Hello"
# 11) Command substitution strips trailing newlines
run_test \
  "Command substitution trims trailing newlines" \
  "printf '<%s>' \"\$(printf 'x\ny\n\n')\"" \
  "<x
y>"
# 12) printf %q shows a shell-escaped representation
run_test \
  "printf %q shows how Bash would re-quote" \
  "printf '%q\n' \"a b * ' q\"" \
  $'a\\ b\\ \\*\\ \'\ q'
# 13) Empty vs unset with defaulting
run_test \
  'Parameter expansion default: ${var:-default}' \
  "unset v; printf '%s\n' \"\${v:-default}\"" \
  "default"
run_test \
  'Empty string still triggers :- default' \
  "v=''; printf '%s\n' \"\${v:-default}\"" \
  "default"
# 14) Backslash escapes inside double quotes (but not all)
run_test \
  "Backslash inside double quotes only escapes \$ \" \\ and newline" \
  "printf '%s\n' \"A\\nB \\$ \\\" \\\\ * ?\"" \
  "A\\nB $ \" \\ * ?"
# 15) Dollar at end vs literal dollar
run_test \
  "Literal trailing dollar in single vs double quotes" \
  "printf '[%s][%s]\n' '\$' \"\$\"" \
  "[$][$]"
# Summary
echo
printf "%sAll tests executed.%s\n" "$BOLD" "$RESET"
