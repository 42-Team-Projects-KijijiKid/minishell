# Exit Test Cases - Minishell

## 📋 Übersicht
Dieser File enthält alle Test Cases, die mit dem `exit` Builtin zusammenhängen, inklusive erwarteter Ergebnisse.

---

## Exit Without Arguments

### Test 1: Exit ohne Argumente
```bash
exit
```
**Erwartetes Ergebnis:** Shell wird beendet
**Exit Status:** Letzter Exit-Status der Shell (normalerweise 0)
**Verhalten:** Minishell terminiert

---

## Exit With Empty String

### Test 2: Exit mit leerem String
```bash
exit ""
```
**Erwartetes Ergebnis:** Fehlermeldung
```
bash: exit: : numeric argument required
```
**Exit Status:** 2 (oder 255 je nach bash-Version)
**Verhalten:** Shell wird mit Exit-Status 2 beendet

---

## Exit With Multiple Arguments

### Test 3: Exit mit zwei Null-Argumenten
```bash
exit 0 0
```
**Erwartetes Ergebnis:** Fehlermeldung
```
bash: exit: too many arguments
```
**Exit Status:** 1
**Verhalten:** Shell wird NICHT beendet, nur Fehlermeldung ausgegeben

---

### Test 4: Exit mit zwei String-Argumenten
```bash
exit something somethingv2
```
**Erwartetes Ergebnis:** Fehlermeldung für nicht-numerisches Argument
```
bash: exit: something: numeric argument required
```
**Exit Status:** 2 (oder 255)
**Verhalten:** Shell wird mit Exit-Status 2 beendet

---

### Test 5: Exit mit einem numerischen Argument
```bash
exit 1 2
```
**Erwartetes Ergebnis:** Fehlermeldung
```
bash: exit: too many arguments
```
**Exit Status:** 1
**Verhalten:** Shell wird NICHT beendet

---

### Test 6: Exit mit drei Argumenten
```bash
exit 1 2 3
```
**Erwartetes Ergebnis:** Fehlermeldung
```
bash: exit: too many arguments
```
**Exit Status:** 1
**Verhalten:** Shell wird NICHT beendet

---

### Test 7: Exit mit Buchstabe und Zahlen
```bash
exit A 2 3
```
**Erwartetes Ergebnis:** Fehlermeldung für nicht-numerisches Argument
```
bash: exit: A: numeric argument required
```
**Exit Status:** 2 (oder 255)
**Verhalten:** Shell wird mit Exit-Status 2 beendet

---

### Test 8: Exit mit Text-Argument
```bash
exit cd ..
```
**Erwartetes Ergebnis:** Fehlermeldung für nicht-numerisches Argument
```
bash: exit: cd: numeric argument required
```
**Exit Status:** 2 (oder 255)
**Verhalten:** Shell wird mit Exit-Status 2 beendet

---

### Test 9: Exit mit mehreren 42-Argumenten
```bash
exit 42 42 42 42 42
```
**Erwartetes Ergebnis:** Fehlermeldung
```
bash: exit: too many arguments
```
**Exit Status:** 1
**Verhalten:** Shell wird NICHT beendet

---

### Test 10: Exit mit zwei gleichen Argumenten
```bash
exit 42 42
```
**Erwartetes Ergebnis:** Fehlermeldung
```
bash: exit: too many arguments
```
**Exit Status:** 1
**Verhalten:** Shell wird NICHT beendet

---

## Exit With String and Number Mix

### Test 11: Exit mit Buchstabe und Zahl (A zuerst)
```bash
exit A 1
```
**Erwartetes Ergebnis:** Fehlermeldung für nicht-numerisches Argument
```
bash: exit: A: numeric argument required
```
**Exit Status:** 2 (oder 255)
**Verhalten:** Shell wird mit Exit-Status 2 beendet

---

### Test 12: Exit mit Zahl und Buchstabe (Zahl zuerst)
```bash
exit 1 A
```
**Erwartetes Ergebnis:** Fehlermeldung
```
bash: exit: too many arguments
```
**Exit Status:** 1
**Verhalten:** Shell wird NICHT beendet

---

## Exit With Positive Numbers

### Test 13: Exit mit +100 in Quotes
```bash
exit "+100"
```
**Erwartetes Ergebnis:** Shell wird beendet
**Exit Status:** 100
**Verhalten:** Shell terminiert mit Exit-Status 100

---

### Test 14: Exit mit +1
```bash
exit +1
```
**Erwartetes Ergebnis:** Shell wird beendet
**Exit Status:** 1
**Verhalten:** Shell terminiert mit Exit-Status 1

---

## Exit With Negative Numbers

### Test 15: Exit mit -100 in Quotes
```bash
exit "-100"
```
**Erwartetes Ergebnis:** Shell wird beendet
**Exit Status:** 156 (256 - 100 = 156, da Exit-Status modulo 256 berechnet wird)
**Hinweis:** Negative Zahlen werden als (256 + (n % 256)) berechnet
**Verhalten:** Shell terminiert mit Exit-Status 156

---

### Test 16: Exit mit -1
```bash
exit -1
```
**Erwartetes Ergebnis:** Shell wird beendet
**Exit Status:** 255 (256 - 1 = 255)
**Verhalten:** Shell terminiert mit Exit-Status 255

---

### Test 17: Exit mit großer negativer Zahl
```bash
exit -12560
```
**Erwartetes Ergebnis:** Shell wird beendet
**Exit Status:** Berechnung: -12560 % 256 = -16, dann 256 + (-16) = 240
**Exit Status:** 240
**Verhalten:** Shell terminiert mit Exit-Status 240

---

### Test 18: Exit mit sehr großer negativer Zahl (out of range)
```bash
exit -9223372036854775805
```
**Erwartetes Ergebnis:** Shell wird beendet
**Exit Status:** Berechnung durch Modulo 256
**Hinweis:** -9223372036854775805 % 256 = -253, dann 256 + (-253) = 3
**Exit Status:** 3
**Verhalten:** Shell terminiert mit Exit-Status 3

---

## Exit Status Testing with Commands

### Test 19: Exit-Status von fehlgeschlagenem Befehl
```bash
/bin/cat 42
echo $?
```
**Erwartetes Ergebnis:**
```
/bin/cat: 42: No such file or directory
1
```
**Exit Status von cat:** 1
**Hinweis:** Testet, ob $? korrekt gesetzt wird

---

### Test 20: Exit-Status von erfolgreichem Befehl zweimal verwendet
```bash
/bin/echo 42
expr $? + $?
```
**Erwartetes Ergebnis:**
```
42
0
```
**Hinweis:** Erstes $? ist 0 (von echo), zweites $? ist auch 0 (da echo erfolgreich war)
**Ergebnis von expr:** 0

---

### Test 21: Exit-Status von fehlgeschlagenem Befehl in expr
```bash
/bin/cat 42
expr $? + $?
```
**Erwartetes Ergebnis:**
```
/bin/cat: 42: No such file or directory
2
```
**Hinweis:** $? ist 1 (von cat), expr rechnet 1 + 1 = 2
**Exit Status von expr:** 0 (expr selbst war erfolgreich)

---

## Exit Modulo 256 Behavior

### Hinweis: Exit-Status wird immer modulo 256 berechnet

**Beispiele:**
- `exit 0` → Exit-Status: 0
- `exit 1` → Exit-Status: 1
- `exit 255` → Exit-Status: 255
- `exit 256` → Exit-Status: 0 (256 % 256)
- `exit 257` → Exit-Status: 1 (257 % 256)
- `exit 300` → Exit-Status: 44 (300 % 256)
- `exit 1000` → Exit-Status: 232 (1000 % 256)
- `exit -1` → Exit-Status: 255
- `exit -2` → Exit-Status: 254
- `exit -256` → Exit-Status: 0
- `exit -257` → Exit-Status: 255

---

## Edge Cases Summary

### Wichtige Regeln für Exit:

1. **Ohne Argumente:** Beendet Shell mit letztem Exit-Status
2. **Mit einem numerischen Argument:** Beendet Shell mit diesem Status (modulo 256)
3. **Mit mehreren Argumenten:** Fehlermeldung "too many arguments", Shell wird NICHT beendet, Exit-Status 1
4. **Mit nicht-numerischem Argument:** Fehlermeldung "numeric argument required", Shell wird beendet mit Exit-Status 2 (oder 255)
5. **Mit leerem String:** Wie nicht-numerisches Argument
6. **Positive Zahlen mit +:** Akzeptiert (z.B. +100 → 100)
7. **Negative Zahlen:** Werden modulo 256 berechnet und dann von 256 subtrahiert
8. **Sehr große Zahlen:** Werden modulo 256 berechnet

---

## Special Cases

### Test 22: Exit nach mehreren echo -n Befehlen
```bash
echo -n -n -n 42
exit
```
**Erwartetes Ergebnis:** 
```
42
```
Shell wird mit letztem Exit-Status beendet (0, da echo erfolgreich war)

---

### Test 23: Exit nach mehreren echo Befehlen
```bash
echo -n -n -n -n 42
exit
```
**Erwartetes Ergebnis:** 
```
42
```
Shell wird mit Exit-Status 0 beendet

---

## Test-Szenarien für Debugging

### Szenario 1: Exit-Status Chain
```bash
/bin/cat 42
echo $?
```
**Erwartung:** `1` wird ausgegeben (Fehler-Status von cat)

---

### Szenario 2: Exit mit mehreren Argumenten stoppt nicht
```bash
exit 1 2 3
echo "Still alive"
```
**Erwartung:** 
```
bash: exit: too many arguments
Still alive
```
Shell läuft weiter!

---

### Szenario 3: Exit mit ungültigem Argument stoppt Shell
```bash
exit ABC
echo "Never reached"
```
**Erwartung:** 
```
bash: exit: ABC: numeric argument required
```
Shell wird beendet, "Never reached" wird NICHT ausgegeben

---

## Summary

**Gesamt Test Cases:** 23+

**Kategorien:**
- Exit Without Arguments: 1 Test
- Exit With Empty String: 1 Test
- Exit With Multiple Arguments: 10 Tests
- Exit With String and Number Mix: 2 Tests
- Exit With Positive Numbers: 2 Tests
- Exit With Negative Numbers: 4 Tests
- Exit Status Testing: 3 Tests
- Special Cases: 2 Tests

**Wichtigste Testpunkte:**
1. ✅ Exit ohne Argumente
2. ✅ Exit mit einem numerischen Argument
3. ✅ Exit mit mehreren Argumenten (sollte Fehler geben, Shell NICHT beenden)
4. ✅ Exit mit nicht-numerischen Argumenten (sollte Shell beenden mit Status 2)
5. ✅ Exit mit leeren Strings
6. ✅ Modulo 256 Berechnung für Exit-Status
7. ✅ Negative Zahlen korrekt behandeln
8. ✅ Sehr große Zahlen (overflow)
9. ✅ Positive Zahlen mit + Prefix
10. ✅ Exit-Status-Verkettung mit $?

**Häufigste Fehlerquellen:**
1. Mehrere Argumente: Shell wird NICHT beendet (Exit-Status 1)
2. Nicht-numerische Argumente: Shell WIRD beendet (Exit-Status 2)
3. Modulo 256 Berechnung bei großen Zahlen
4. Negative Zahlen richtig umrechnen
5. Leerer String wird als nicht-numerisch behandelt
