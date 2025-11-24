# Export Test Cases - Minishell

## 📋 Übersicht
Dieser File enthält alle Test Cases, die mit dem `export` Builtin zusammenhängen, inklusive erwarteter Ergebnisse.

---

## Basic Export Tests

### Test 1: Export ohne Argumente
```bash
export
```
**Erwartetes Ergebnis:** Liste aller exportierten Variablen im Format `declare -x VAR="value"` (sortiert)

---

### Test 2: Export mit Builtin-Namen
```bash
export export
```
**Erwartetes Ergebnis:** Fehlermeldung - `export: 'export': not a valid identifier` oder ähnlich
**Exit Status:** 1

---

### Test 3: Export mit Builtin-Namen (echo)
```bash
export echo
```
**Erwartetes Ergebnis:** Fehlermeldung - `export: 'echo': not a valid identifier` (wenn kein Wert)
**Alternative:** Wenn bash es erlaubt, wird eine Variable `echo` ohne Wert exportiert
**Exit Status:** Abhängig von bash-Verhalten

---

### Test 4: Export mit Builtin-Namen (cd)
```bash
export cd
```
**Erwartetes Ergebnis:** Fehlermeldung - `export: 'cd': not a valid identifier` (wenn kein Wert)
**Alternative:** Variable `cd` ohne Wert exportiert
**Exit Status:** Abhängig von bash-Verhalten

---

### Test 5: Export mit einfachem Namen
```bash
export test
```
**Erwartetes Ergebnis:** Variable `test` wird exportiert (ohne Wert, falls noch nicht gesetzt)
**Exit Status:** 0

---

### Test 6: Export mit Großbuchstaben
```bash
export TEST
```
**Erwartetes Ergebnis:** Variable `TEST` wird exportiert (ohne Wert)
**Exit Status:** 0

---

### Test 7: Export mit leerem Wert
```bash
export TEST=
```
**Erwartetes Ergebnis:** Variable `TEST` wird mit leerem String exportiert
```
declare -x TEST=""
```
**Exit Status:** 0

---

### Test 8: Export mit Wert
```bash
export TEST=123
```
**Erwartetes Ergebnis:** Variable `TEST` wird mit Wert "123" exportiert
```
declare -x TEST="123"
```
**Exit Status:** 0

---

### Test 9: Export mit Underscores am Anfang
```bash
export ___TEST=123
```
**Erwartetes Ergebnis:** Variable `___TEST` wird mit Wert "123" exportiert
```
declare -x ___TEST="123"
```
**Exit Status:** 0

---

### Test 10: Export mit Underscore am Anfang
```bash
export _TEST=100
```
**Erwartetes Ergebnis:** Variable `_TEST` wird mit Wert "100" exportiert
```
declare -x _TEST="100"
```
**Exit Status:** 0

---

### Test 11: Export mit Underscores
```bash
export TES_T=123
```
**Erwartetes Ergebnis:** Variable `TES_T` wird mit Wert "123" exportiert
```
declare -x TES_T="123"
```
**Exit Status:** 0

---

### Test 12: Export mit Underscore am Ende
```bash
export TEST_=123
```
**Erwartetes Ergebnis:** Variable `TEST_` wird mit Wert "123" exportiert
```
declare -x TEST_="123"
```
**Exit Status:** 0

---

### Test 13: Export mit nur Underscores
```bash
export ________=123
```
**Erwartetes Ergebnis:** Variable `________` wird mit Wert "123" exportiert
```
declare -x ________="123"
```
**Exit Status:** 0

---

## Export with Multiple Variables

### Test 14: Export einzelne Variable mit Wert
```bash
export a="asd"
```
**Erwartetes Ergebnis:** Variable `a` wird mit Wert "asd" exportiert
```
declare -x a="asd"
```
**Exit Status:** 0

---

### Test 15: Export mehrere Variablen gleichzeitig
```bash
export a="asd" b="de" o= c="hellomi" X
```
**Erwartetes Ergebnis:** 
- Variable `a` mit Wert "asd"
- Variable `b` mit Wert "de"
- Variable `o` mit leerem Wert ""
- Variable `c` mit Wert "hellomi"
- Variable `X` ohne Wert (oder leer)
```
declare -x a="asd"
declare -x b="de"
declare -x o=""
declare -x c="hellomi"
declare -x X
```
**Exit Status:** 0

---

### Test 16: Export mit ungültiger Syntax (Text nach Variablen)
```bash
export miert ne lehetne ezt is
```
**Erwartetes Ergebnis:** Nur `miert` wird als Variable exportiert (ohne Wert), Rest wird ignoriert oder Fehler
**Alternative:** Fehlermeldung für `ne`, `lehetne`, `ezt`, `is`
**Exit Status:** 0 oder 1 (abhängig von bash)

---

## Export - Variable Overwriting

### Test 17: Mehrfache Zuweisung - Letzter Wert zählt
```bash
export L=amazing L=ok L=cool
echo $L
```
**Erwartetes Ergebnis:** 
```
cool
```
Variable `L` erhält den letzten zugewiesenen Wert "cool"
**Exit Status:** 0

---

### Test 18: Export überschreiben mit erneutem Export
```bash
export L=amazing L=ok L=cool
export L=ok
echo $L
```
**Erwartetes Ergebnis:** 
```
ok
```
Variable `L` wird zu "ok" geändert
**Exit Status:** 0

---

### Test 19: Mehrfache Zuweisung verschiedener Variablen
```bash
export T=a T=b T=c
echo $T
```
**Erwartetes Ergebnis:** 
```
c
```
Variable `T` erhält den letzten Wert "c"
**Exit Status:** 0

---

## Export - Invalid Variable Names

### Test 20: Export mit doppeltem Minus
```bash
export --TEST=123
```
**Erwartetes Ergebnis:** Fehlermeldung
```
export: '--TEST=123': not a valid identifier
```
**Exit Status:** 1

---

### Test 21: Export mit Bindestrich im Namen
```bash
export TE-ST=100
```
**Erwartetes Ergebnis:** Fehlermeldung
```
export: 'TE-ST=100': not a valid identifier
```
**Exit Status:** 1

---

### Test 22: Export mit Minus am Anfang
```bash
export -TEST=100
```
**Erwartetes Ergebnis:** Fehlermeldung
```
export: '-TEST=100': not a valid identifier
```
**Exit Status:** 1

---

### Test 23: Export mit Minus vor Gleichheitszeichen
```bash
export TEST-=100
```
**Erwartetes Ergebnis:** Fehlermeldung
```
export: 'TEST-=100': not a valid identifier
```
**Exit Status:** 1

---

### Test 24: Export mit Gleichheitszeichen im Variablennamen
```bash
export TES=T=""
```
**Erwartetes Ergebnis:** Variable `TES` wird mit Wert `T=` exportiert
```
declare -x TES="T="
```
**Exit Status:** 0

---

### Test 25: Export mit Plus im Namen
```bash
export TE+S=T=""
```
**Erwartetes Ergebnis:** Fehlermeldung
```
export: 'TE+S=T=': not a valid identifier
```
**Exit Status:** 1

---

### Test 26: Export mit Punkt im Namen
```bash
export TES.T=123
```
**Erwartetes Ergebnis:** Fehlermeldung
```
export: 'TES.T=123': not a valid identifier
```
**Exit Status:** 1

---

### Test 27: Export mit Plus vor Gleichheitszeichen
```bash
export TES+T=123
```
**Erwartetes Ergebnis:** Fehlermeldung
```
export: 'TES+T=123': not a valid identifier
```
**Exit Status:** 1

---

### Test 28: Export mit doppeltem Gleichheitszeichen
```bash
export TES=T=123
```
**Erwartetes Ergebnis:** Variable `TES` wird mit Wert "T=123" exportiert
```
declare -x TES="T=123"
```
**Exit Status:** 0

---

### Test 29: Export mit geschweifter Klammer zu
```bash
export TES}T=123
```
**Erwartetes Ergebnis:** Fehlermeldung
```
export: 'TES}T=123': not a valid identifier
```
**Exit Status:** 1

---

### Test 30: Export mit geschweifter Klammer auf
```bash
export TES{T=123
```
**Erwartetes Ergebnis:** Fehlermeldung
```
export: 'TES{T=123': not a valid identifier
```
**Exit Status:** 1

---

### Test 31: Export mit Bindestrich (nochmal)
```bash
export TES-T=123
```
**Erwartetes Ergebnis:** Fehlermeldung
```
export: 'TES-T=123': not a valid identifier
```
**Exit Status:** 1

---

### Test 32: Export mit Sternchen
```bash
export TE*ST=123
```
**Erwartetes Ergebnis:** Fehlermeldung oder Wildcard-Expansion
```
export: 'TE*ST=123': not a valid identifier
```
**Exit Status:** 1

---

### Test 33: Export mit Raute
```bash
export TES#T=123
```
**Erwartetes Ergebnis:** Fehlermeldung
```
export: 'TES#T=123': not a valid identifier
```
**Exit Status:** 1

---

### Test 34: Export mit @-Zeichen
```bash
export TES@T=123
```
**Erwartetes Ergebnis:** Fehlermeldung
```
export: 'TES@T=123': not a valid identifier
```
**Exit Status:** 1

---

### Test 35: Export mit Ausrufezeichen
```bash
export TES!T=123
```
**Erwartetes Ergebnis:** Fehlermeldung
```
export: 'TES!T=123': not a valid identifier
```
**Exit Status:** 1

---

### Test 36: Export mit $? im Namen
```bash
export TES$?T=123
```
**Erwartetes Ergebnis:** Variable wird mit expandiertem $? erstellt (z.B. `TES0T`)
**Alternative:** Fehlermeldung
**Exit Status:** Variiert

---

### Test 37: Export mit Caret
```bash
export TES^T=123
```
**Erwartetes Ergebnis:** Fehlermeldung
```
export: 'TES^T=123': not a valid identifier
```
**Exit Status:** 1

---

### Test 38: Export mit Tilde und Backslash
```bash
export TES\~T=123
```
**Erwartetes Ergebnis:** Fehlermeldung
```
export: 'TES~T=123': not a valid identifier
```
**Exit Status:** 1

---

### Test 39: Export mit += Operator
```bash
export TEST+=100
```
**Erwartetes Ergebnis:** Fehlermeldung (bash unterstützt +=, aber im Kontext prüfen)
```
export: 'TEST+=100': not a valid identifier
```
**Alternative:** Wert wird an bestehende Variable angehängt
**Exit Status:** 1 (oder 0 wenn += unterstützt wird)

---

## Export - Special Values

### Test 40: Export und Überprüfung neuer Variable
```bash
/bin/echo $HALLO42
env | grep HALLO42
export HALLO42=42
/bin/echo $HALLO42
env | grep HALLO42
```
**Erwartetes Ergebnis:**
```
(leer - Variable existiert noch nicht)
(keine Ausgabe - Variable nicht in env)
42
HALLO42=42
```
**Exit Status:** 0

---

### Test 41: Export und Überschreiben von HOME
```bash
/bin/echo $HOME
env | grep HOME
export HOME=42
/bin/echo $HOME
env | grep HOME
```
**Erwartetes Ergebnis:**
```
/home/username (oder aktueller HOME-Pfad)
HOME=/home/username
42
HOME=42
```
**Exit Status:** 0

---

### Test 42: Export mit Underscore-Variable
```bash
export TES_T=123
/bin/echo $TES_T
env | grep TES_T
```
**Erwartetes Ergebnis:**
```
123
TES_T=123
```
**Exit Status:** 0

---

### Test 43: Export mit Gleichheitszeichen im Wert
```bash
export HELLO42=T=""
/bin/echo $HELLO42
env | grep HELLO42
env | grep HELLO42=T=
```
**Erwartetes Ergebnis:**
```
T=
HELLO42=T=
(keine Ausgabe - es gibt keine Variable HELLO42=T=)
```
**Exit Status:** 0

---

### Test 44: Export mit leerem Wert prüfen
```bash
/bin/echo $mini_test
env | grep mini_test
export mini_test=
/bin/echo $mini_test
env | grep mini_test
```
**Erwartetes Ergebnis:**
```
(leer)
(keine Ausgabe)
(leer)
mini_test=
```
**Exit Status:** 0

---

### Test 45: Export USER mit leerem Wert
```bash
export USER=
env | grep USER
```
**Erwartetes Ergebnis:**
```
USER=
```
USER wird zu leerem String
**Exit Status:** 0

---

### Test 46: Export USER mit Sonderzeichen
```bash
export USER="@?/"
env | grep USER
```
**Erwartetes Ergebnis:**
```
USER=@?/
```
**Exit Status:** 0

---

### Test 47: Export mit Leerzeichen im Wert
```bash
export NEW="4 2"
env | grep NEW
```
**Erwartetes Ergebnis:**
```
NEW=4 2
```
**Exit Status:** 0

---

### Test 48: Export mit Gleichheitszeichen im Wert
```bash
export NEW="4=2"
env | grep NEW
```
**Erwartetes Ergebnis:**
```
NEW=4=2
```
**Exit Status:** 0

---

### Test 49: Export ohne Quotes, Gleichheitszeichen im Wert
```bash
export NEW=4=2
env | grep 4=2
```
**Erwartetes Ergebnis:**
```
NEW=4=2
(keine Ausgabe für grep 4=2 - Variable heißt NEW, nicht 4)
```
**Alternative:** 
```
NEW=4=2
```
**Exit Status:** 0

---

## Export in Pipes

### Test 50: Export in Pipe
```bash
export GHOST=123 | env | grep GHOST
```
**Erwartetes Ergebnis:** Keine Ausgabe - GHOST wird nur im linken Teil der Pipe exportiert, nicht im rechten
```
(leer - GHOST ist in der Subshell von env nicht sichtbar)
```
**Exit Status:** 1 (grep findet nichts)

---

## Export with Special Syntax

### Test 51: Export mit Quotes und Mixed Quotes
```bash
"e"'x''p''o''r''t' L=T
echo $T
```
**Erwartetes Ergebnis:** 
Der Befehl wird zu `export L=T` evaluiert
```
(leer - Variable T existiert nicht, nur L wird exportiert)
```
Variable `L` wird mit Wert "T" exportiert
**Exit Status:** 0

---

## Summary

**Gesamt Test Cases:** 51

**Kategorien:**
- Basic Export Tests: 13 Tests
- Export with Multiple Variables: 3 Tests
- Export Variable Overwriting: 3 Tests
- Export Invalid Variable Names: 20 Tests
- Export Special Values: 10 Tests
- Export in Pipes: 1 Test
- Export with Special Syntax: 1 Test

**Häufigste Fehlerquellen:**
1. Ungültige Variablennamen (Sonderzeichen, Bindestriche, etc.)
2. Export mit mehrfachen Zuweisungen
3. Export in Pipes (Scope-Probleme)
4. Leerzeichen und Quotes im Parsing
5. Gleichheitszeichen in Werten vs. Namen
