# Echo Test Cases - Minishell

## 📋 Übersicht
Dieser File enthält alle Test Cases, die mit dem `echo` Builtin zusammenhängen, inklusive erwarteter Ergebnisse.

---

## Basic Echo Tests

### Test 1: Echo ohne Argumente
```bash
echo
```
**Erwartetes Ergebnis:**
```
(leere Zeile)
```
**Exit Status:** 0
**Hinweis:** Gibt nur einen Newline aus

---

### Test 2: Echo mit einzelner Zahl
```bash
echo 1
```
**Erwartetes Ergebnis:**
```
1
```
**Exit Status:** 0

---

### Test 3: Echo mit gemischten Quotes und Text
```bash
echo "  "Hello "World "
```
**Erwartetes Ergebnis:**
```
  Hello World 
```
**Exit Status:** 0
**Hinweis:** Spaces in Quotes werden beibehalten, zwischen Argumenten ein Space

---

### Test 4: Echo mit Single Quotes und Wörtern
```bash
echo '  ' Hello World
```
**Erwartetes Ergebnis:**
```
   Hello World
```
**Exit Status:** 0
**Hinweis:** Drei Argumente: `'  '`, `Hello`, `World`

---

### Test 5: Echo mit Single Quotes um jedes Wort
```bash
echo '  'Hello 'World '
```
**Erwartetes Ergebnis:**
```
  Hello World 
```
**Exit Status:** 0

---

### Test 6: Echo mit vielen leeren Quotes
```bash
echo " "" " ' ' " " ' ' " "
```
**Erwartetes Ergebnis:**
```
   ' '   ' '  
```
**Hinweis:** Bash behandelt Single Quotes in Double Quotes als literal, und umgekehrt
**Alternative Ausgabe (je nach Interpretation):**
```
      
```
**Exit Status:** 0

---

## Echo with -n Flag

### Test 7: Echo -n mit Zahl
```bash
echo -n 42
```
**Erwartetes Ergebnis:**
```
42
```
(ohne Newline am Ende)
**Exit Status:** 0

---

### Test 8: Echo -n mit weiterer Flag
```bash
echo -n 42 -n
```
**Erwartetes Ergebnis:**
```
42 -n
```
(ohne Newline)
**Exit Status:** 0
**Hinweis:** Zweites `-n` wird als Argument behandelt, nicht als Flag

---

### Test 9: Echo mit mehreren -n Flags
```bash
echo -n -n -n 42
```
**Erwartetes Ergebnis:**
```
42
```
(ohne Newline)
**Exit Status:** 0
**Hinweis:** Alle aufeinanderfolgenden `-n` Flags werden erkannt

---

### Test 10: Echo mit vier -n Flags
```bash
echo -n -n -n -n 42
```
**Erwartetes Ergebnis:**
```
42
```
(ohne Newline)
**Exit Status:** 0

---

### Test 11: Echo -n mit einzelnem Argument
```bash
echo -n test1
```
**Erwartetes Ergebnis:**
```
test1
```
(ohne Newline)
**Exit Status:** 0

---

### Test 12: Echo -n mit Quotes
```bash
echo -n "test1 test2"
```
**Erwartetes Ergebnis:**
```
test1 test2
```
(ohne Newline)
**Exit Status:** 0

---

### Test 13: Echo -n mit mehreren Argumenten
```bash
echo -n "test1 test2" test3
```
**Erwartetes Ergebnis:**
```
test1 test2 test3
```
(ohne Newline)
**Exit Status:** 0

---

### Test 14: Echo -n mit gemischten Quotes
```bash
echo -n " test1 test2 " 'test3 '
```
**Erwartetes Ergebnis:**
```
 test1 test2  test3 
```
(ohne Newline)
**Exit Status:** 0

---

### Test 15: Echo -n mit Tabs
```bash
echo -n test1		test2
```
**Erwartetes Ergebnis:**
```
test1 test2
```
(ohne Newline)
**Hinweis:** Tabs zwischen Argumenten werden zu einem Space reduziert
**Exit Status:** 0

---

### Test 16: Echo -n zweimal
```bash
echo -n -n test1
```
**Erwartetes Ergebnis:**
```
test1
```
(ohne Newline)
**Exit Status:** 0

---

### Test 17: Echo mit fünf -n Flags
```bash
echo -n -n -n -n -n test1
```
**Erwartetes Ergebnis:**
```
test1
```
(ohne Newline)
**Exit Status:** 0

---

### Test 18: Echo -n mit ungültigem Flag-Format
```bash
echo -n -n -nasd
```
**Erwartetes Ergebnis:**
```
-nasd
```
(ohne Newline)
**Hinweis:** `-nasd` ist kein gültiges Flag, wird als Argument ausgegeben
**Exit Status:** 0

---

### Test 19: Echo -n mit gemischtem Flag
```bash
echo -n -n -n-nnnnn
```
**Erwartetes Ergebnis:**
```
-n-nnnnn
```
(ohne Newline)
**Hinweis:** `-n-nnnnn` wird als Argument behandelt
**Exit Status:** 0

---

### Test 20: Echo mit vielen -n Flags (komplex)
```bash
echo -n -nnnnnnn -n -nnn -nnnnn -n-n
```
**Erwartetes Ergebnis:**
```
-n-n
```
(ohne Newline)
**Hinweis:** `-nnnnnnn`, `-nnn`, `-nnnnn` sind gültige Flags (nur `n` mehrfach), `-n-n` ist ungültig (wegen Bindestrich)
**Exit Status:** 0

---

### Test 21: Echo -n mit Text am Ende
```bash
echo -n -nnnnnnn -n -nnn -nnnnn -n feel my pain
```
**Erwartetes Ergebnis:**
```
feel my pain
```
(ohne Newline)
**Exit Status:** 0

---

### Test 22: Echo -n komplex
```bash
echo -n -n -n-n
```
**Erwartetes Ergebnis:**
```
-n-n
```
(ohne Newline)
**Hinweis:** `-n-n` ist ungültiges Flag-Format
**Exit Status:** 0

---

### Test 23: Echo mit vielen n's
```bash
echo -nnnnnnnnnnnn
```
**Erwartetes Ergebnis:**
```
(leer)
```
(ohne Newline)
**Hinweis:** `-nnnnnnnnnnnn` ist ein gültiges Flag (nur n's)
**Exit Status:** 0

---

## Echo with Tabs

### Test 24: Echo mit Tabs zwischen Argumenten
```bash
echo test1		test2
```
**Erwartetes Ergebnis:**
```
test1 test2
```
**Hinweis:** Tabs werden zu einem Space reduziert
**Exit Status:** 0

---

### Test 25: /bin/echo mit Tabs
```bash
/bin/echo test1		test2
```
**Erwartetes Ergebnis:**
```
test1 test2
```
**Hinweis:** Externe echo-Befehle verhalten sich gleich
**Exit Status:** 0

---

### Test 26: /bin/echo -n mit Tabs
```bash
/bin/echo -n test1		test2
```
**Erwartetes Ergebnis:**
```
test1 test2
```
(ohne Newline)
**Exit Status:** 0

---

## Echo with Variable-Based Flags

### Test 27: Echo mit Flag aus Variable
```bash
export T=n
echo "-"$T$T
```
**Erwartetes Ergebnis:**
```
-nn
```
**Hinweis:** `-nn` ist ein gültiges Flag, aber es kommt NICHT am Anfang, daher wird es als Text ausgegeben
**Exit Status:** 0

---

### Test 28: Echo mit komplexer Variable
```bash
export T=-nnnnnnnn"nnnnnnn "
echo $T
```
**Erwartetes Ergebnis:**
```
-nnnnnnnnnnnnnnn 
```
**Hinweis:** Variable wird expandiert und als Argument behandelt (nicht als Flag)
**Exit Status:** 0

---

### Test 29: Echo mit großgeschriebenem Echo
```bash
export T=-"n                    "
Echo $T
```
**Erwartetes Ergebnis:**
```
bash: Echo: command not found
```
**Exit Status:** 127
**Hinweis:** `Echo` (großgeschrieben) ist ein anderer Befehl

---

### Test 30: Echo mit Flag-String in Variable
```bash
export T="-n test1 -n test 2"
echo $T
```
**Erwartetes Ergebnis:**
```
-n test1 -n test 2
```
**Hinweis:** Variable wird expandiert, aber Flags funktionieren nur am Anfang des Befehls
**Exit Status:** 0

---

### Test 31: Echo mit langen n-Strings
```bash
export T=nnnnnnnn
echo "-""$T"nnnnnnnnnnnnn -nnnnnnnn"$T" '-'"$T"
```
**Erwartetes Ergebnis:**
```
-nnnnnnnnnnnnnnnnnnnnnn -nnnnnnnnnnnnnnnn -nnnnnnnn
```
**Exit Status:** 0

---

### Test 32: Echo mit gemischten Quotes und Variable
```bash
export T=nnnnnnnn
echo "-""$T"nnnnnnnnnnnnn -nnnnnnnn"$T" '-''$T'
```
**Erwartetes Ergebnis:**
```
-nnnnnnnnnnnnnnnnnnnnnn -nnnnnnnnnnnnnnnn -nnnnnnnn
```
**Exit Status:** 0

---

### Test 33: Echo mit Single Quotes um Variable
```bash
export T=nnnnnnnn
echo "-"'$T'nnnnnnnnnnnnn -nnnnnnnn'$T' '-'"$T "
```
**Erwartetes Ergebnis:**
```
-$Tnnnnnnnnnnnnn -nnnnnnnn$T -nnnnnnnn 
```
**Hinweis:** In Single Quotes wird $T nicht expandiert
**Exit Status:** 0

---

### Test 34: Echo mit Variable ohne Quotes
```bash
export T=nnnnnnnn
echo "-"'$T'nnnnnnnnnnnnn -nnnnnnnn$T '-''$T '
```
**Erwartetes Ergebnis:**
```
-$Tnnnnnnnnnnnnn -nnnnnnnnnnnnnnnn -nnnnnnnn 
```
**Exit Status:** 0

---

## Echo via Variables (Command Construction)

### Test 35: Echo-Befehl teilweise aus Variable
```bash
export T=ech
echo $To
```
**Erwartetes Ergebnis:**
```
(leer)
```
**Hinweis:** Variable `To` existiert nicht, daher leere Ausgabe
**Exit Status:** 0

---

### Test 36: Echo aus Variable zusammensetzen
```bash
export T=ech
echo $T"o"
```
**Erwartetes Ergebnis:**
```
echo
```
**Hinweis:** Dies führt NICHT echo aus, sondern gibt "echo" als Text aus
**Exit Status:** 0

---

### Test 37: Echo-Kommando mit Space
```bash
export T=ech
echo $T"o "
```
**Erwartetes Ergebnis:**
```
echo 
```
**Exit Status:** 0

---

### Test 38: Echo-Kommando mit Flag
```bash
export T=ech
echo $T"o -n"
```
**Erwartetes Ergebnis:**
```
echo -n
```
**Exit Status:** 0

---

### Test 39: Variable zu echo expandieren
```bash
export T=ech
echo $T'o'
```
**Erwartetes Ergebnis:**
```
echo
```
**Exit Status:** 0

---

### Test 40: Variable zu echo mit Space
```bash
export T=ech
echo $T'o '
```
**Erwartetes Ergebnis:**
```
echo 
```
**Exit Status:** 0

---

### Test 41: Befehl aus mehreren Variablen (Execution)
```bash
export T=e E=c S=h L=o
$T$E$S$L
```
**Erwartetes Ergebnis:**
```
(leere Zeile)
```
**Hinweis:** Variablen werden zu "echo" zusammengesetzt und ausgeführt
**Exit Status:** 0

---

### Test 42: Befehl mit überschriebener Variable
```bash
export T=e E=c S=h L=o L=ok
$T$E$S$L
```
**Erwartetes Ergebnis:**
```
(leer)
```
**Hinweis:** L wird zu "ok" überschrieben, daher wird $T$E$S$L zu "echok" (kein gültiger Befehl)
**Alternative:** Fehlermeldung "echok: command not found"
**Exit Status:** 127 (command not found)

---

### Test 43: Echo-Befehl mit -n Flag aus Variablen
```bash
export T=e E=c S=h L=o
$T$E$S$L -n
```
**Erwartetes Ergebnis:**
```
(leer, ohne Newline)
```
**Hinweis:** "echo -n" wird ausgeführt
**Exit Status:** 0

---

### Test 44: Echo-Befehl mit E am Anfang
```bash
export T=E E=c S=h L=o
$T$E$S$L -n
```
**Erwartetes Ergebnis:**
```
bash: Ecsho: command not found
```
**Exit Status:** 127
**Hinweis:** T=E, daher wird "Ecsho" aufgerufen (kein gültiger Befehl)

---

### Test 45: Echo mit -nn Flag
```bash
export T=E E=c S=h L=o
$T$E$S$L -nn
```
**Erwartetes Ergebnis:**
```
bash: Ecsho: command not found
```
**Exit Status:** 127

---

### Test 46: Echo aus Variablen mit -nn
```bash
export T=e E=c S=h L=o
$T$E$S$L -nn
```
**Erwartetes Ergebnis:**
```
(leer, ohne Newline)
```
**Hinweis:** "echo -nn" wird ausgeführt
**Exit Status:** 0

---

### Test 47: Echo mit Quote in Variable
```bash
export T=e E=c S=h L=o
$T$E"c"$L -nn
```
**Erwartetes Ergebnis:**
```
(leer, ohne Newline)
```
**Hinweis:** Expandiert zu "echo -nn"
**Exit Status:** 0

---

### Test 48: Echo mit Großbuchstabe in Variable
```bash
export T=e E=c S=h L=o
$T$E"C"$L -nn
```
**Erwartetes Ergebnis:**
```
bash: ecCo: command not found
```
**Exit Status:** 127
**Hinweis:** "ecCo" ist kein gültiger Befehl

---

### Test 49: Echo mit leeren Quotes
```bash
export T=e E=c S=h L=o
$T$E"C"$L "" -""n
```
**Erwartetes Ergebnis:**
```
bash: ecCo: command not found
```
**Exit Status:** 127

---

## Undefined Variables in Echo

### Test 50: Echo mit nicht existierender Variable
```bash
$NOVAR
```
**Erwartetes Ergebnis:**
```
(nichts - leerer Befehl)
```
**Exit Status:** 0
**Hinweis:** Leere Variable führt zu leerem Befehl

---

### Test 51: Befehl aus nicht existierender Variable
```bash
export T="s"
l$T
```
**Erwartetes Ergebnis:**
```
bash: ls: command not found
```
**Alternative:** Wenn `ls` existiert, wird es ausgeführt
**Exit Status:** 0 (wenn ls erfolgreich) oder 127

---

### Test 52: ls mit Flag aus Variable
```bash
export T="s"
l$T -a
```
**Erwartetes Ergebnis:**
Führt `ls -a` aus (falls ls verfügbar)
**Exit Status:** 0 oder 127

---

### Test 53: Variable am Ende des Befehls
```bash
export T="l"
$Ts
```
**Erwartetes Ergebnis:**
```
bash: ls: command not found
```
**Alternative:** Führt `ls` aus (wenn verfügbar)
**Exit Status:** 0 oder 127

---

### Test 54: Variable mit Flag
```bash
export T="l"
$Ts -a
```
**Erwartetes Ergebnis:**
Führt `ls -a` aus (falls verfügbar)
**Exit Status:** 0 oder 127

---

## Summary

**Gesamt Test Cases:** 54+

**Kategorien:**
- Basic Echo Tests: 6 Tests
- Echo with -n Flag: 17 Tests
- Echo with Tabs: 3 Tests
- Echo with Variable-Based Flags: 8 Tests
- Echo via Variables (Command Construction): 15 Tests
- Undefined Variables in Echo: 5 Tests

**Wichtigste Testpunkte:**
1. ✅ Echo ohne Argumente (gibt nur Newline aus)
2. ✅ Echo mit -n Flag (unterdrückt Newline)
3. ✅ Mehrere -n Flags werden alle erkannt
4. ✅ -n muss am Anfang stehen (in Variable funktioniert nicht)
5. ✅ Gültige -n Flags: `-n`, `-nn`, `-nnn`, etc. (nur n's)
6. ✅ Ungültige Flags: `-n-n`, `-nasd` (werden als Argumente ausgegeben)
7. ✅ Tabs zwischen Argumenten werden zu einem Space
8. ✅ Quotes werden korrekt verarbeitet
9. ✅ Variable Expansion vor Befehlsausführung
10. ✅ Command Construction aus Variablen möglich

**Häufigste Fehlerquellen:**
1. -n Flag erkennung: Muss am Anfang stehen, nur n's sind erlaubt
2. Tabs vs. Spaces: Tabs zwischen Argumenten → ein Space
3. Quote-Handling: Single vs. Double Quotes
4. Variable Expansion: In Single Quotes keine Expansion
5. Command Construction: Variablen können zu Befehlen zusammengesetzt werden
6. Flag in Variablen: Funktioniert nicht, da Flags nur am Anfang erkannt werden
