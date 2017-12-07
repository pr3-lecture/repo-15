## Übungsblatt 2

Daniel Meng, 1427948, repo-14<br />
Julian Braasch, 1512359, repo-15<br />
Mustafa Yildiz, 1411880, repo-16<br />

### Aufgabe 1

a) Insert

```xml
(defun insert (tree val)
  (append tree (list val))
)
```

b) Insert aus Datei

```xml
(defun insertFile (tree filename)
  (open "baum.txt" :output)
)
```

d) Size

```xml
(defun size (tree)
  (cond ((null tree) nil)
        ((listp (car tree)) (append (my-reverseR (cdr tree)) (list (my-reverseR (car tree)))))
        (T (append (my-reverseR (cdr tree)) (list (car tree))))
  )
)
```

i) isEmpty

```xml
(defun isEmpty (tree)
  (if (null tree) 'TRUE 'FALSE))
)
```