#!/usr/bin/env bash
set -euo pipefail

# Ensure we're in a git repo and have staged changes
git rev-parse --git-dir >/dev/null 2>&1 || { echo "Not a git repo."; exit 1; }
if git diff --cached --quiet; then
  echo "No staged changes. Stage files first (e.g., git add -p)."
  exit 1
fi

types=(feat fix docs style refactor perf test chore)
echo "Select type:"
select t in "${types[@]}"; do
  [[ -n "${t:-}" ]] && break
done

read -rp "Optional scope (e.g. auth, ui) — leave blank to skip: " scope
read -rp "Short summary (imperative, ≤ 50 chars): " subject

# Trim and validate subject
subject="$(echo "$subject" | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')"
if [[ -z "$subject" || ${#subject} -gt 50 ]]; then
  echo "Summary is required and must be ≤ 50 chars."; exit 1
fi

read -rp "Is this a BREAKING change? (y/N): " breaking
read -rp "Issues to close (e.g. 'Closes #12, #34') — optional: " issues

# Compose header
header="$t"
[[ -n "$scope" ]] && header+="($scope)"
[[ "$breaking" =~ ^[Yy]$ ]] && header+="!"
header+=": $subject"

# Compose body via editor (optional)
tmp="$(mktemp)"
{
  echo "$header"
  echo
  echo "# Write a longer body below (optional). Lines >72 chars will be flagged by hook."
  echo "# Remove these commented lines before saving."
} > "$tmp"

"${EDITOR:-vi}" "$tmp"

# Strip comment lines starting with #
msg="$(sed '/^#/d' "$tmp")"
printf "%s\n" "$msg" > "$tmp"

# Add footer for issues/breaking (if not already in body)
{
  echo
  [[ "$breaking" =~ ^[Yy]$ ]] && echo "BREAKING CHANGE: <describe the breaking change>"
  [[ -n "$issues" ]] && echo "$issues"
} >> "$tmp"

echo
echo "---- Commit message preview ----"
cat "$tmp"
echo "--------------------------------"

read -rp "Proceed with commit? (Y/n): " ok
if [[ ! "$ok" =~ ^([Yy]|)$ ]]; then
  echo "Aborted."; rm -f "$tmp"; exit 1
fi

git commit -F "$tmp"
rm -f "$tmp"

