;;; -*- Mode: LISP; Syntax: Common-Lisp; Package: CL-USER -*-
 
(in-package :cl-user)

(defparameter *lracer-filenames*
  '("nrql-symbols-1-9-2"
    "lracer-package-1-9-1"
    "lracer-1-9-1"
    #-:nrql-dev "lracer-nrql-stubs-1-9-2"
    "lracer-test-support-1-9-1"))

(defun compile-load-lracer (&optional (directory "racer:lracer;"))
  (loop for filename in *lracer-filenames* 
        for pathname = (merge-pathnames (pathname filename)
                                        (pathname directory))
        do
        (compile-file (merge-pathnames pathname (make-pathname :type "lisp"))
                      :verbose t)
        (load pathname :verbose t))) 

