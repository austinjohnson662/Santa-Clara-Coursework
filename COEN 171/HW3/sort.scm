; vi:ai:lisp:sm


(define (filter f lst)
  (cond
	((null? lst) lst)
	((f car(lst)) (cons car(a) filter f (cdr(lst))))
	(else (filter f (cdr(lst))))))


(define (quicksort lst)
  (if null? lst 
	(else let*
		  (h (car(lst)))
		  (t (cdr(lst)))
		  (below (lambda (x) (< x h)))
		  (above (lambda (x) (>= x h))))
	(append (quicksort (filter below t)) (cons h (quicksort (filter above t))))))
