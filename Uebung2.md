## Übungsblatt 2

Daniel Meng, 1427948, repo-14<br />
Julian Braasch, 1512359, repo-15<br />
Mustafa Yildiz, 1411880, repo-16<br />

### Aufgabe 1

#### insert tree val
Fügt val in den Baum tree ein und gibt als Ergebnis den ergänzten Baum zurück. Am besten wird dabei ein neuer Baum erzeugt.

```xml
(defun insert (tree val)
  (cond (
        (null tree) (append (list val)))
        ((< val (car tree)) (append (list (car tree) (cadr tree) (insert (caddr tree) val))))
        ((> val (car tree)) (append (list (car tree) (insert (cadr tree) val) (caddr tree))))
        (T (append (list (car tree) (cadr tree) (caddr tree))))
  )
)
```

#### insert tree filename
Fügt die int-Werte, die in der Datei stehen in den Baum ein.

```xml
...
```

#### contains tree val
Testet, ob val im Baum vorhanden ist.

```xml
(defun contains (tree val)
  (if (endp tree) nil
  (or (equal val (car tree))
  (or (contains (cadr tree) val) (contains (caddr tree) val))))
)
```

#### size tree
Ermittelt die Anzahl der Knoten im Baum.

```xml
(defun size (tree)
  (cond ((null tree) 0)
        ((listp (car tree)) (+ (size (car tree)) (size (cdr tree))))
        (T (+ 1 (size (cdr tree))))
  )
)
```

#### height tree
Ermittelt die Höhe des Baums.

```xml
(defun height (tree)
  (if (endp tree)
    0
    (+ 1 (max (height (cadr tree)) (height (caddr tree))))
  )
)
```

#### getMax tree
Liefert das größte Element im Baum.

```xml
(defun getMax (tree)
  (if (endp tree)
  0
  (max (car tree) (max (getMax (cadr tree)) (getMax (caddr tree))))
  )
)
```

#### getMin tree
Liefert das kleinste Element im Baum.

```xml
(defun getMin (tree)
  (if (endp tree)
  0
  (min (car tree) (min (getMin (cadr tree)) (getMin (caddr tree))))
  )
)
```

#### remove tree val
Entfernt val aus dem Baum und gibt als Ergebnis den geänderten Baum zurück.
Wenn ein innerer Knoten gelöscht wird, dann erstetzen Sie ihn durch den kleinsten Knoten in dessen rechtem Teilbaum.

```xml
(defun remove_val (tree value)
  (cond
  ((null tree) nil)
  ((> value (car tree)) (append (list (car tree)) (list (cadr tree)) (list (remove_val (caddr tree) value))))
  ((< value (car tree)) (append (list (car tree)) (list (remove_val (cadr tree) value)) (list (caddr tree))))
  (t (cond
    ((and (null (cadr tree)) (null (caddr tree))) nil)
    ((null (caddr tree)) (append (list (getMax (cadr tree))) (list (remove_val (cadr tree) (getMax (cadr tree)))) (list (caddr tree))))
    (t (append (list (getMin (caddr tree))) (list(cadr tree)) (list (remove_val (caddr tree) (getMin (caddr tree))))))
	)
  )
  )
)
```

#### isEmpty tree
true genau dann, wenn der Baum leer ist.

```xml
(defun isEmpty (tree)
  (if (null tree) T NIL)
)
```

#### addAll tree otherTree
Fügt alle Elemente des übergebenen Baums (otherTree) in den aktuellen Baum tree ein.

```xml
(defun addAll (tree otherTree)
    (setq otherTree (printLevelorder otherTree))
    (loop
    (setq tree (insert tree (car otherTree)))
    (setq otherTree (cdr otherTree))
    (when (endp otherTree) (return tree))
)
)
```

#### printLevelorder tree
Gibt Baum in Levelorder aus.

```xml
(defun printGivenLevel (tree level)
    (if (endp tree)
    0
    (cond ((= 1 level)  (list (car tree)))
        ((append (printGivenLevel (cadr tree) (1- level))
        (printGivenLevel (caddr tree) (1- level))))
    )
    )
)
    
(defun printLevelorder (tree)
    (setq h (height tree))
    (setq i 1)
    (setq r (list (car tree)))
    (loop
    (setq i  (+ i 1))
    (setq r (append r (printGivenLevel tree i)))
    (when (= i h) (return r))
    )
)
```