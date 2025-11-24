# Failed Tests - Minishell (Vollständige Analyse)

**Testdatum:** 24. November 2025  
**Tester:** mstest m (42_minishell_tester)  
**Erfolgsrate:** ~89.3% (457+ von 512+ Tests bestanden)

---

## 📋 Inhaltsverzeichnis

- [Übersicht](#übersicht)
- [Compare Parsing](#compare-parsing)
- [Parsing Hell](#parsing-hell)
- [Builtins](#builtins)
- [Statistik nach Fehlertyp](#statistik-nach-fehlertyp)
- [Prioritäten](#prioritäten)

---

## Übersicht

### Fehlertypen-Legende
- **❌ STD_OUT**: Falsche Standardausgabe
- **❌ STD_ERR**: Falsche Fehlerausgabe  
- **❌ EXIT_CODE**: Falscher Exit-Code

---

# Compare Parsing

## Test 65: Tabs in echo (STD_OUT ❌)
**Quelle:** `0_compare_parsing.sh:134`

```bash
/bin/echo test1		test2
```

**Fehlertyp:** ❌ STD_OUT  
**Status:** STD_ERR: ✅ | EXIT_CODE: ✅

**Problem:** Multiple Tabs/Spaces zwischen Argumenten werden nicht korrekt zu einem Space reduziert

**Erwartetes Ergebnis:**
```
test1 test2
```

---

## Test 72: Tabs in echo -n (STD_OUT ❌)
**Quelle:** `0_compare_parsing.sh:148`

```bash
/bin/echo -n test1		test2
```

**Fehlertyp:** ❌ STD_OUT  
**Status:** STD_ERR: ✅ | EXIT_CODE: ✅

**Problem:** Multiple Tabs zwischen Argumenten mit -n Flag

**Erwartetes Ergebnis:**
```
test1 test2
```
(ohne Newline am Ende)

---

# Parsing Hell

## Test 2: Redirection mit Quotes (STD_ERR ❌)
**Quelle:** `10_parsing_hell.sh:7`

```bash
>">" asd
```

**Fehlertyp:** ❌ STD_ERR  
**Status:** STD_OUT: ✅ | EXIT_CODE: ✅

**Problem:** Redirection mit quoted Filename erzeugt falsche Fehlermeldung

**Erwartung:** Sollte Datei namens ">" erstellen und "asd" als Befehl ausführen

---

## Test 4: Append mit Variable (STD_ERR ❌)
**Quelle:** `10_parsing_hell.sh:14`

```bash
>> '$USER'
```

**Fehlertyp:** ❌ STD_ERR  
**Status:** STD_OUT: ✅ | EXIT_CODE: ✅

**Problem:** Append-Redirection mit quoted Variable

---

## Test 12: Heredoc mit Variable als Delimiter (STD_OUT ❌ + EXIT_CODE ❌)
**Quelle:** `10_parsing_hell.sh:32`

```bash
cat << $USER
why
not
$USER
```

**Fehlertyp:** ❌ STD_OUT ❌ EXIT_CODE  
**Status:** STD_ERR: ✅  
**Exit-Codes:** minishell(130) | bash(0)

**Problem:** Heredoc-Delimiter ist eine Variable. Exit-Code 130 (SIGINT) statt 0

**Erwartung:** Variable wird expandiert und als Delimiter verwendet

---

## Test 14: Heredoc mit quoted Variable (STD_OUT ❌ + EXIT_CODE ❌)
**Quelle:** `10_parsing_hell.sh:40`

```bash
cat << "$USER"
why
not
$USER
```

**Fehlertyp:** ❌ STD_OUT ❌ EXIT_CODE  
**Status:** STD_ERR: ✅  
**Exit-Codes:** minishell(130) | bash(0)

**Problem:** Heredoc mit quoted Variable als Delimiter

---

## Test 15: Heredoc mit partiellem Quote (STD_OUT ❌ + EXIT_CODE ❌)
**Quelle:** `10_parsing_hell.sh:45`

```bash
cat << "$US"E"R"
because
we
love
bash
$USER
```

**Fehlertyp:** ❌ STD_OUT ❌ EXIT_CODE  
**Status:** STD_ERR: ✅  
**Exit-Codes:** minishell(130) | bash(0)

**Problem:** Heredoc-Delimiter mit mixed quotes

---

## Test 17: Append mit quoted Variable (STD_ERR ❌)
**Quelle:** `10_parsing_hell.sh:54`

```bash
>> "$H"OM"E"
```

**Fehlertyp:** ❌ STD_ERR  
**Status:** STD_OUT: ✅ | EXIT_CODE: ✅

**Problem:** Append-Redirection mit partiellem Quote

---

## Test 30: Export mit -n Flag in Variable (STD_OUT ❌)
**Quelle:** `10_parsing_hell.sh:96`

```bash
export T="-n test1 -n test 2"
echo $T
```

**Fehlertyp:** ❌ STD_OUT  
**Status:** STD_ERR: ✅ | EXIT_CODE: ✅

**Erwartetes Ergebnis:**
```
-n test1 -n test 2
```

**Problem:** Variable-Expansion mit Flag-String

---

## Test 54: Leere Variable als Befehl (EXIT_CODE ❌)
**Quelle:** `10_parsing_hell.sh:159`

```bash
$NOVAR
```

**Fehlertyp:** ❌ EXIT_CODE  
**Status:** STD_OUT: ✅ | STD_ERR: ✅  
**Exit-Codes:** minishell(127) | bash(0)

**Problem:** Nicht existierende Variable ergibt Exit-Code 127 statt 0

**Erwartung:** Leerer Befehl sollte Exit-Code 0 ergeben

---

## Test 57: Variable mit Teilstring (EXIT_CODE ❌)
**Quelle:** `10_parsing_hell.sh:167`

```bash
export T="l"
$Ts -a
```

**Fehlertyp:** ❌ EXIT_CODE  
**Status:** STD_OUT: ✅ | STD_ERR: ✅  
**Exit-Codes:** minishell(127) | bash(0)

**Problem:** $Ts expandiert zu leerem String (Variable Ts existiert nicht)

**Kontext:** Vorheriger Befehl setzt T="l", aber $Ts versucht Variable "Ts" zu lesen

---

## Test 58: Variable am Ende (STD_ERR ❌)
**Quelle:** `10_parsing_hell.sh:170`

```bash
export T="l"
$Ts
```

**Fehlertyp:** ❌ STD_ERR  
**Status:** STD_OUT: ✅ | EXIT_CODE: ✅

**Problem:** Fehler-Meldung bei nicht existierender Variable

---

## Test 77: Pipe in Variable (ALLE ❌)
**Quelle:** `10_parsing_hell.sh:216`

```bash
export T="echo segfault | grep segfault"
$T
```

**Fehlertyp:** ❌ STD_OUT ❌ STD_ERR ❌ EXIT_CODE  
**Exit-Codes:** minishell(127) | bash(0)

**Problem:** **KRITISCH** - Alle drei Fehlertypen

**Erwartung:** Variable-Expansion sollte NICHT Pipe interpretieren (Pipe ist literal Text)

**Erwartetes Ergebnis:**
```
bash: echo segfault | grep segfault: command not found
```

---

## Test 78: Variable mit -n String (STD_OUT ❌)
**Quelle:** `10_parsing_hell.sh:219`

```bash
export T=-nnnnnnnn"nnnnnnn "
echo $T
```

**Fehlertyp:** ❌ STD_OUT  
**Status:** STD_ERR: ✅ | EXIT_CODE: ✅

**Erwartetes Ergebnis:**
```
-nnnnnnnnnnnnnnn 
```

---

## Test 89: Heredoc als Variable (STD_ERR ❌)
**Quelle:** `10_parsing_hell.sh:247`

```bash
export T="<<"
$T .
```

**Fehlertyp:** ❌ STD_ERR  
**Status:** STD_OUT: ✅ | EXIT_CODE: ✅

**Problem:** Heredoc-Operator in Variable sollte nicht interpretiert werden

---

## Test 101: Viele Quotes (STD_ERR ❌)
**Quelle:** `10_parsing_hell.sh:272`

```bash
'''''''''''''''' echo ok
```

**Fehlertyp:** ❌ STD_ERR  
**Status:** STD_OUT: ✅ | EXIT_CODE: ✅

**Problem:** 16 leere Single-Quotes hintereinander sollten zu leerem String kollabieren

**Erwartetes Ergebnis:**
```
ok
```

---

## Test 115: Dollar-Slash (STD_OUT ❌)
**Quelle:** `10_parsing_hell.sh:303`

```bash
echo $/ $/ 
```

**Fehlertyp:** ❌ STD_OUT  
**Status:** STD_ERR: ✅ | EXIT_CODE: ✅

**Erwartetes Ergebnis:**
```
$/ $/
```

**Problem:** $/ sollte literal bleiben (keine Variable)

---

## Test 118: Dollar-Slash mit Quotes (STD_OUT ❌)
**Quelle:** `10_parsing_hell.sh:309`

```bash
echo $/"$/"
```

**Fehlertyp:** ❌ STD_OUT  
**Status:** STD_ERR: ✅ | EXIT_CODE: ✅

**Erwartetes Ergebnis:**
```
$/$/ 
```

---

## Test 123: Redirection mit Pipe (EXIT_CODE ❌)
**Quelle:** `10_parsing_hell.sh:319`

```bash
>| echo sure
```

**Fehlertyp:** ❌ EXIT_CODE  
**Status:** STD_OUT: ✅ | STD_ERR: ✅  
**Exit-Codes:** minishell(2) | bash(127)

**Problem:** Exit-Code falsch - >| ist ungültige Redirection

**Erwartung:** bash gibt 127 (command not found für "|")

---

## Test 124: cd mit doppeltem Minus (STD_ERR ❌ + EXIT_CODE ❌)
**Quelle:** `10_parsing_hell.sh:321`

```bash
cd --
```

**Fehlertyp:** ❌ STD_ERR ❌ EXIT_CODE  
**Status:** STD_OUT: ✅  
**Exit-Codes:** minishell(1) | bash(0)

**Problem:** cd -- sollte zu HOME wechseln (-- wird ignoriert)

**Erwartung:** Exit-Code 0, keine Fehlermeldung

---

# Builtins

## Test 61: Tabs in echo (STD_OUT ❌)
**Quelle:** `1_builtins.sh:127`

```bash
echo test1		test2
```

**Fehlertyp:** ❌ STD_OUT  
**Status:** STD_ERR: ✅ | EXIT_CODE: ✅

**Problem:** Multiple Tabs zwischen Argumenten

---

## Test 68: Tabs in echo -n (STD_OUT ❌)
**Quelle:** `1_builtins.sh:142`

```bash
echo -n test1		test2
```

**Fehlertyp:** ❌ STD_OUT  
**Status:** STD_ERR: ✅ | EXIT_CODE: ✅

---

## Tests 94-99 & 125: pwd Tests (STD_OUT ❌)
**Quellen:** 
- `1_builtins.sh:201` - Test 94
- `1_builtins.sh:205` - Test 95  
- `1_builtins.sh:217` - Test 98
- `1_builtins.sh:221` - Test 99
- `1_builtins.sh:302` - Test 125

```bash
pwd
```

**Fehlertyp:** ❌ STD_OUT  
**Status:** STD_ERR: ✅ | EXIT_CODE: ✅

**Problem:** pwd gibt falschen Pfad zurück

**Kontext:** Diese Tests folgen auf cd-Operationen:
- Test 94/95: Nach `cd .` und `cd "./././"`
- Test 98/99: Nach `cd /` und `cd '/'`
- Test 125: Nach `cd -`

---

## Test 102: cd mit zu vielen Slashes (STD_ERR ❌ + EXIT_CODE ❌)
**Quelle:** `1_builtins.sh:233`

```bash
cd '/////' 2>/dev/null
```

**Fehlertyp:** ❌ STD_ERR ❌ EXIT_CODE  
**Status:** STD_OUT: ✅  
**Exit-Codes:** minishell(1) | bash(0)

**Problem:** cd sollte zu / wechseln (Exit-Code 0), gibt aber Fehler

---

## Test 105: cd mit nicht existierendem Verzeichnis (STD_ERR ❌)
**Quelle:** `1_builtins.sh:239`

```bash
cd "doesntexist" 2>/dev/null
```

**Fehlertyp:** ❌ STD_ERR  
**Status:** STD_OUT: ✅ | EXIT_CODE: ✅

**Problem:** Fehlermeldung wird trotz 2>/dev/null ausgegeben

---

## Test 107: cd mit nicht existierendem Verzeichnis 2 (STD_ERR ❌)
**Quelle:** `1_builtins.sh:243`

```bash
cd "wtf" 2>/dev/null
```

**Fehlertyp:** ❌ STD_ERR  
**Status:** STD_OUT: ✅ | EXIT_CODE: ✅

---

## Test 122: cd mit mehreren Parent-Dirs (ALLE ❌)
**Quelle:** `1_builtins.sh:290`

```bash
cd ../../
```

**Fehlertyp:** ❌ STD_OUT ❌ STD_ERR ❌ EXIT_CODE  
**Exit-Codes:** minishell(1) | bash(0)

**Problem:** **KRITISCH** - cd schlägt fehl bei ../../

---

## Tests 131-132: pwd nach cd - (STD_OUT ❌ + STD_ERR ❌)
**Quellen:**
- `1_builtins.sh:328` - Test 131
- `1_builtins.sh:333` - Test 132

```bash
cd -
pwd
```

**Fehlertyp:** ❌ STD_OUT ❌ STD_ERR  
**Status:** EXIT_CODE: ✅

**Problem:** pwd nach `cd -` gibt falschen Pfad

---

## Test 136: env mit nicht existierender Variable (EXIT_CODE ❌)
**Quelle:** `1_builtins.sh:352`

```bash
env | grep DOESNT_EXIST
```

**Fehlertyp:** ❌ EXIT_CODE  
**Status:** STD_OUT: ✅ | STD_ERR: ✅  
**Exit-Codes:** minishell(0) | bash(1)

**Problem:** Exit-Code sollte 1 sein (grep findet nichts), ist aber 0

---

## Test 140: env mit Argument (ALLE ❌)
**Quelle:** `1_builtins.sh:360`

```bash
env what
```

**Fehlertyp:** ❌ STD_OUT ❌ STD_ERR ❌ EXIT_CODE  
**Exit-Codes:** minishell(0) | bash(127)

**Problem:** **KRITISCH** - env akzeptiert keine Argumente in minishell subject

**Erwartung:** Fehlermeldung "env: 'what': No such file or directory" + Exit 127

---

## Test 150: export ohne Argumente (STD_OUT ❌)
**Quelle:** `1_builtins.sh:390`

```bash
export
```

**Fehlertyp:** ❌ STD_OUT  
**Status:** STD_ERR: ✅ | EXIT_CODE: ✅

**Problem:** Export ohne Argumente sollte alle exportierten Variablen zeigen

**Erwartetes Format:**
```
declare -x HOME="/home/user"
declare -x PATH="/usr/bin:..."
...
```

---

## Test 165: export mit ungültigem Namen (EXIT_CODE ❌)
**Quelle:** `1_builtins.sh:420`

```bash
export --TEST=123
```

**Fehlertyp:** ❌ EXIT_CODE  
**Status:** STD_OUT: ✅ | STD_ERR: ✅  
**Exit-Codes:** minishell(1) | bash(2)

**Problem:** Exit-Code sollte 2 sein (numeric required), nicht 1

---

## Tests 169-171: export mit ungültigen Namen (STD_ERR ❌)
**Quellen:**
- `1_builtins.sh:428` - Test 169: `export TE-ST=100`
- `1_builtins.sh:432` - Test 171: `export TEST-=100`

**Fehlertyp:** ❌ STD_ERR  
**Status:** STD_OUT: ✅ | EXIT_CODE: ✅

**Problem:** Fehlermeldung hat falsches Format

**Erwartete Fehlermeldung:**
```
bash: export: `TE-ST=100': not a valid identifier
```

---

## Test 170: export mit -Prefix (EXIT_CODE ❌)
**Quelle:** `1_builtins.sh:430`

```bash
export -TEST=100
```

**Fehlertyp:** ❌ EXIT_CODE  
**Status:** STD_OUT: ✅ | STD_ERR: ✅  
**Exit-Codes:** minishell(1) | bash(2)

---

## Tests 177-184: export mit Sonderzeichen (STD_ERR ❌)
**Quellen:**
- `1_builtins.sh:444`: `export TES^T=123`
- `1_builtins.sh:446`: `export TES\~T=123`
- `1_builtins.sh:448`: `export TEST+=100`
- `1_builtins.sh:450`: `export TES#T=123`
- `1_builtins.sh:454`: `export TES@T=123`
- `1_builtins.sh:456`: `export TES!T=123`
- `1_builtins.sh:458`: `export TES$?T=123`

**Fehlertyp:** ❌ STD_ERR  
**Status:** STD_OUT: ✅ | EXIT_CODE: ✅

**Problem:** Fehlermeldungsformat bei ungültigen Variablennamen

---

## Test 185: export mit += (EXIT_CODE ❌)
**Quelle:** `1_builtins.sh:460`

```bash
export TEST+=100
```

**Fehlertyp:** ❌ EXIT_CODE  
**Status:** STD_OUT: ✅ | STD_ERR: ✅  
**Exit-Codes:** minishell(1) | bash(2)

---

## Tests 189-192: export mit Sonderzeichen 2 (STD_ERR ❌)
**Quellen:**
- `1_builtins.sh:468`: `export TE*ST=123`
- `1_builtins.sh:470`: `export TES.T=123`
- `1_builtins.sh:472`: `export TES+T=123`
- `1_builtins.sh:474`: `export TES}T=123`

**Fehlertyp:** ❌ STD_ERR  
**Status:** STD_OUT: ✅ | EXIT_CODE: ✅

---

## Tests 197-199: export mit Sonderzeichen 3 (STD_ERR ❌)
**Quellen:**
- `1_builtins.sh:484`: `export TES{T=123`
- `1_builtins.sh:486`: `export TES-T=123`
- `1_builtins.sh:488`: `export TE+S=T=""`

**Fehlertyp:** ❌ STD_ERR  
**Status:** STD_OUT: ✅ | EXIT_CODE: ✅

---

## Test 200: export mit leeren Quotes (EXIT_CODE ❌)
**Quelle:** `1_builtins.sh:490`

```bash
export TES=T=""
```

**Fehlertyp:** ❌ EXIT_CODE  
**Status:** STD_OUT: ✅ | STD_ERR: ✅  
**Exit-Codes:** minishell(1) | bash(0)

**Problem:** Dies ist VALIDE - setzt TES="T="

---

## Test 202: export mit Builtin-Name (STD_OUT ❌)
**Quelle:** `1_builtins.sh:496`

```bash
export export
export cd
export echo
```

**Fehlertyp:** ❌ STD_OUT  
**Status:** STD_ERR: ✅ | EXIT_CODE: ✅

**Problem:** Variablenexport mit Builtin-Namen sollte möglich sein

---

## Test 231: exit mit leerem String (STD_ERR ❌ + EXIT_CODE ❌)
**Quelle:** `1_builtins.sh:566`

```bash
exit ""
```

**Fehlertyp:** ❌ STD_ERR ❌ EXIT_CODE  
**Status:** STD_OUT: ✅  
**Exit-Codes:** minishell(0) | bash(2)

**Problem:** Leerer String ist kein gültiges numerisches Argument

**Erwartete Fehlermeldung:**
```
bash: exit: : numeric argument required
```
**Erwarteter Exit-Code:** 2 (oder 255)

---

# Statistik nach Fehlertyp

## Nur STD_OUT Fehler
**Anzahl:** 16 Tests

### Compare Parsing (2)
- Test 65: Tabs in /bin/echo
- Test 72: Tabs in /bin/echo -n

### Parsing Hell (4)
- Test 30: Variable mit -n String
- Test 115: $/ expansion
- Test 118: $/ mit quotes
- Test 78: Variable mit -n

### Builtins (10)
- Test 61: Tabs in echo
- Test 68: Tabs in echo -n
- Tests 94, 95, 98, 99, 125: pwd nach cd
- Test 150: export ohne Argumente
- Test 202: export mit Builtin-Namen

---

## Nur STD_ERR Fehler
**Anzahl:** 19 Tests

### Parsing Hell (4)
- Test 2: Redirection mit Quotes
- Test 4: Append mit Variable
- Test 17: Append mit quoted Variable
- Test 58: Variable am Ende
- Test 89: Heredoc als Variable
- Test 101: Viele Quotes

### Builtins (15)
- Test 105, 107: cd mit nicht existierendem Verzeichnis
- Tests 169, 171, 177-184, 189-192, 197-199: export mit ungültigen Namen

---

## Nur EXIT_CODE Fehler
**Anzahl:** 9 Tests

### Parsing Hell (3)
- Test 54: Leere Variable als Befehl
- Test 57: Variable mit Teilstring  
- Test 123: Redirection mit Pipe

### Builtins (6)
- Test 136: env mit grep
- Test 165: export --TEST
- Test 170: export -TEST
- Test 185: export +=
- Test 200: export mit =

---

## STD_OUT + EXIT_CODE
**Anzahl:** 3 Tests

### Parsing Hell (3)
- Test 12: Heredoc mit Variable
- Test 14: Heredoc mit quoted Variable
- Test 15: Heredoc mit partiellem Quote

**Gemeinsames Problem:** Exit-Code 130 (SIGINT) statt 0

---

## STD_ERR + EXIT_CODE
**Anzahl:** 3 Tests

### Parsing Hell (1)
- Test 124: cd --

### Builtins (2)
- Test 102: cd '/////'
- Test 231: exit ""

---

## STD_OUT + STD_ERR
**Anzahl:** 2 Tests

### Builtins (2)
- Tests 131-132: pwd nach cd -

---

## Alle drei Fehler (KRITISCH)
**Anzahl:** 3 Tests

### Parsing Hell (1)
- Test 77: Pipe in Variable

### Builtins (2)
- Test 122: cd ../../
- Test 140: env what

---

# Prioritäten

## 🔴 Kritisch (Alle 3 Fehlertypen)

1. **Test 77** (Parsing Hell): Pipe in Variable
2. **Test 122** (Builtins): cd ../../
3. **Test 140** (Builtins): env what

---

## 🟠 Hoch (Exit-Code-Probleme)

### Exit-Code 1 statt 2 (numeric errors)
- Test 165: export --TEST
- Test 170: export -TEST
- Test 185: export +=

### Exit-Code 130 statt 0 (Heredoc mit Variablen)
- Tests 12, 14, 15: Heredoc-Delimiter als Variable

### Exit-Code 0 statt 1 (Fehler nicht erkannt)
- Test 136: env | grep (leeres Ergebnis)
- Test 200: export TES=T="" (valider Befehl)

### Sonstige Exit-Code-Fehler
- Test 54: Leere Variable (127 → 0)
- Test 57: Variable-Teilstring (127 → 0)
- Test 123: >| redirection (2 → 127)

---

## 🟡 Mittel (STD_ERR-Probleme)

### Export-Fehlermeldungen (15 Tests)
Tests 169, 171, 177-184, 189-192, 197-199

**Problem:** Fehlermeldungsformat bei ungültigen Variablennamen

**Erwartetes Format:**
```
bash: export: `VARNAME=VALUE': not a valid identifier
```

### cd-Fehlermeldungen
- Tests 105, 107: cd mit nicht existierendem Verzeichnis
- Test 102: cd mit zu vielen Slashes

### Sonstige STD_ERR
- Tests 2, 4, 17: Redirection mit Quotes
- Test 58: Variable am Ende
- Test 89: Heredoc-Operator in Variable
- Test 101: Viele Quotes
- Test 231: exit mit leerem String

---

## 🟢 Niedrig (STD_OUT-Probleme)

### Tabs/Spaces (4 Tests)
- Tests 65, 72: /bin/echo mit Tabs
- Tests 61, 68: echo mit Tabs

**Problem:** Multiple Tabs werden nicht zu einem Space reduziert

### pwd-Probleme (7 Tests)
Tests 94, 95, 98, 99, 125, 131, 132

**Problem:** pwd gibt nach bestimmten cd-Operationen falschen Pfad zurück

### Variable-Expansion (4 Tests)
- Test 30, 78: Variable mit -n String
- Test 115, 118: $/ expansion

### Export-Output
- Test 150: export ohne Argumente
- Test 202: export mit Builtin-Namen

---

## Empfohlene Reihenfolge

1. **Kritische Fehler** (Tests 77, 122, 140)
2. **Exit-Code 1→2 bei export** (Tests 165, 170, 185)
3. **Heredoc Exit-Code 130→0** (Tests 12, 14, 15)
4. **Export STD_ERR** (15 Tests)
5. **cd-Probleme** (Tests 102, 105, 107, 122, 124, 131, 132)
6. **pwd-Probleme** (Tests 94, 95, 98, 99, 125, 131, 132)
7. **Tabs/Spaces** (Tests 61, 65, 68, 72)
8. **Variable-Expansion** (Tests 30, 54, 57, 58, 78, 115, 118)
9. **Sonstige** (Rest)

---

## Zusammenfassung

- **Gesamt getestet:** 512+ Tests
- **Fehlgeschlagen:** 55 Tests (10.7%)
- **Bestanden:** 457+ Tests (89.3%)

### Nach Kategorie:
- **Compare Parsing:** 2/89 fehlgeschlagen (97.8% Erfolg)
- **Parsing Hell:** 19/124 fehlgeschlagen (84.7% Erfolg)
- **Builtins:** 34/299 fehlgeschlagen (88.6% Erfolg)

### Häufigste Probleme:
1. **Export-Fehlermeldungen** (15 Tests)
2. **Exit-Code-Fehler** (18 Tests)
3. **pwd-Probleme** (7 Tests)
4. **Tabs/Spaces-Handling** (4 Tests)
5. **Heredoc mit Variablen** (3 Tests)
