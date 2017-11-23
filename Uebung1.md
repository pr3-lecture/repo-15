## Übungsblatt 1

### Aufgabe 1
a) Elemente tauschen

```xml
(defun rotiere (l)
  (append (cdr l) (list (car l)))
)
```

b) Element einfügen

```xml
(defun neues-vorletztes (e l)
  (append (reverse (cdr (reverse l))) (list e) (list (car (reverse l))))
)
```

c) Länge einer Liste berechnen

```xml
(defun my-length (l)
  (do (
      (anz 0 (+ anz 1))
      (listneu l (cdr listneu)))
      ((null listneu) anz)
  )
)
```

d) Länge einer geschachtelten Liste berechnen

```xml
```

e) Listen umkehren

```xml
(defun my-reverse (l) 
  (cond(
       (null l) '())	
       (T (append (my-reverse (cdr l)) (list (car l))))
  )
)
```

f) Geschachtelte Listen umkehren

```xml
(defun my-reverseR (l)
  (cond ((null l) nil)
        ((listp (car l)) (append (my-reverseR (cdr l)) (list (my-reverseR (car l)))))
        (T (append (my-reverseR (cdr l)) (list (car l))))
  )
)

```

### Aufgabe 2
a) Darstellung eines Binärbaums

Das erste Element ist die Wurzel. Die anderen beiden sind Knoten.<br />
Ein Knoten besteht wiederrum aus sich selbst und ein/mehreren Knoten.

b) Baumtraversierung
