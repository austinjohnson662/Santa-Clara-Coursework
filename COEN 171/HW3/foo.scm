; vi:ai:lisp:sm

; an empty node is represented as an empty list
; a nonempty node is represented as a list with three elements:
;    - the first element is the integer data
;    - the second element is the left child
;    - the third element is the right child

; Inserts values in a list into a tree

(define (fold func val lst)
  (if (null? lst) val (fold func (func val (car lst)) (cdr lst))))

(define (build lst)
  (fold (lambda (t v) (insert t v)) '() lst))
