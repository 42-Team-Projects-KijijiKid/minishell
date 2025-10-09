#!/usr/bin/env bash
set -euo pipefail

git rev-parse --git-dir >/dev/null 2>&1 || { echo "Not a git repo."; exit 1; }
HOOK_DIR="$(git rev-parse --git-dir)/hooks"
mkdir -p "$HOOK_DIR"

cat > "$HOOK_DIR/commit-msg" <<"EOF"
#!/usr/bin/env bash
set -euo pipefail

file="$1"
header="$(head -n1 "$file")"

# Conventional header:
# <type>(optional scope)!?: <subject up to 50 chars>
if ! grep -Eq '^(feat|fix|docs|style|refactor|perf|test|chore)(\([a-zA-Z0-9._/-]+\))?!?: .{1,50}$' <<<"$header"; then
  echo "❌ Commit header must match Conventional Commits and ≤50 chars after ':'."
  echo "   Example: feat(auth): add JWT login"
  echo "   Got:     $header"
  exit 1
fi

# If there is a body, it must be separated by a blank line
if [[ $(wc -l < "$file") -gt 1 ]]; then
  second_line="$(sed -n '2p' "$file")"
  if [[ -n "$second_line" ]]; then
    echo "❌ Add a blank line between the header and body."
    exit 1
  fi
fi

# Enforce 72-char limit on body/footer lines (header already checked)
# Skip empty lines
tail -n +3 "$file" | while IFS= read -r line; do
  [[ -z "$line" ]] && continue
  if [[ ${#line} -gt 72 ]]; then
    echo "❌ Body/footer lines should be ≤72 chars:"
    echo "   \"$line\""
    exit 1
  fi
done

exit 0
EOF

chmod +x "$HOOK_DIR/commit-msg"
echo "✅ Installed commit-msg hook in $HOOK_DIR/commit-msg"

git config alias.mgc '!sh -c "scripts/good-commit.sh" -'
echo "✅ Added alias mgc for message commit."
echo " -> Usage:   git mgc"