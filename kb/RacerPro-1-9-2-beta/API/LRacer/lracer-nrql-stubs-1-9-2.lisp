(in-package racer)

;;;
;;;--------------------------------------
;;;  Automatically Generated nRQL Stubs  
;;;          Version: 1.9.2  
;;;--------------------------------------
;;;

(defun store-substrate-for-current-abox (filename)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "store-substrate-for-current-abox"
      (mapcar #'transform-s-expr (list filename))
      (mapcar #'transform-s-expr nil)))))



(defun restore-all-substrates (filename)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "restore-all-substrates"
      (mapcar #'transform-s-expr (list filename))
      (mapcar #'transform-s-expr nil)))))



(defun restore-substrate (filename)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "restore-substrate"
      (mapcar #'transform-s-expr (list filename))
      (mapcar #'transform-s-expr nil)))))



(defun store-all-substrates (filename)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "store-all-substrates"
      (mapcar #'transform-s-expr (list filename))
      (mapcar #'transform-s-expr nil)))))



(defun store-substrate-for-abox (filename &optional for-abox type-of-substrate)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "store-substrate-for-abox"
      (mapcar #'transform-s-expr (list filename for-abox type-of-substrate))
      (mapcar #'transform-s-expr nil)))))



(defun get-nrql-version nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "get-nrql-version"))))

(defun del-rcc-edge1 (&rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "del-rcc-edge1"
      (mapcar #'transform-s-expr (list))
      (mapcar #'transform-s-expr args)))))



(defun del-rcc-node1 (&rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "del-rcc-node1"
      (mapcar #'transform-s-expr (list))
      (mapcar #'transform-s-expr args)))))



(defun rcc-edge-label1 (&rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "rcc-edge-label1"
      (mapcar #'transform-s-expr (list))
      (mapcar #'transform-s-expr args)))))



(defun rcc-node-label1 (&rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "rcc-node-label1"
      (mapcar #'transform-s-expr (list))
      (mapcar #'transform-s-expr args)))))



(defun rcc-edge1 (&rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "rcc-edge1"
      (mapcar #'transform-s-expr (list))
      (mapcar #'transform-s-expr args)))))



(defun rcc-node1 (&rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "rcc-node1"
      (mapcar #'transform-s-expr (list))
      (mapcar #'transform-s-expr args)))))



(defun rcc-related1 (&rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "rcc-related1"
      (mapcar #'transform-s-expr (list))
      (mapcar #'transform-s-expr args)))))



(defun rcc-instance1 (&rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "rcc-instance1"
      (mapcar #'transform-s-expr (list))
      (mapcar #'transform-s-expr args)))))



(defun rcc-consistent-p (&optional abox type-of-substrate)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "rcc-consistent-p"
      (mapcar #'transform-s-expr (list abox type-of-substrate))
      (mapcar #'transform-s-expr nil)))))



(defun create-rcc-edge (&rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "create-rcc-edge"
      (mapcar #'transform-s-expr (list))
      (mapcar #'transform-s-expr args)))))



(defun create-rcc-node (&rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "create-rcc-node"
      (mapcar #'transform-s-expr (list))
      (mapcar #'transform-s-expr args)))))



(defun set-rcc-box (name &optional rcc-type)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "set-rcc-box"
      (mapcar #'transform-s-expr (list name rcc-type))
      (mapcar #'transform-s-expr nil)))))



(defun set-mirror-data-box (name)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "set-mirror-data-box"
      (mapcar #'transform-s-expr (list name))
      (mapcar #'transform-s-expr nil)))))



(defun description-implies-p (a b)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "description-implies-p"
      (mapcar #'transform-s-expr (list a b))
      (mapcar #'transform-s-expr nil)))))



(defun set-data-box (name)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "set-data-box"
      (mapcar #'transform-s-expr (list name))
      (mapcar #'transform-s-expr nil)))))



(defun get-data-edge-label (from to &key abox type-of-substrate)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "get-data-edge-label"
      (mapcar #'transform-s-expr (list from to abox abox type-of-substrate type-of-substrate))
      (mapcar #'transform-s-expr nil)))))



(defun get-data-node-label (name &key abox type-of-substrate)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "get-data-node-label"
      (mapcar #'transform-s-expr (list name abox abox type-of-substrate type-of-substrate))
      (mapcar #'transform-s-expr nil)))))



(defun delete-data-edge (from to &key abox type-of-substrate told-info-p)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "delete-data-edge"
      (mapcar #'transform-s-expr (list from to abox abox type-of-substrate type-of-substrate told-info-p told-info-p))
      (mapcar #'transform-s-expr nil)))))



(defun delete-data-node (name &key abox type-of-substrate told-info-p)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "delete-data-node"
      (mapcar #'transform-s-expr (list name abox abox type-of-substrate type-of-substrate told-info-p told-info-p))
      (mapcar #'transform-s-expr nil)))))



(defun create-data-edge (from to descr &key abox type-of-substrate racer-descr told-info-p)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "create-data-edge"
      (mapcar #'transform-s-expr (list from to descr abox abox type-of-substrate type-of-substrate racer-descr racer-descr told-info-p told-info-p))
      (mapcar #'transform-s-expr nil)))))



(defun create-data-node (name &key abox type-of-substrate racer-descr descr told-info-p)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "create-data-node"
      (mapcar #'transform-s-expr (list name abox abox type-of-substrate type-of-substrate racer-descr racer-descr descr descr told-info-p told-info-p))
      (mapcar #'transform-s-expr nil)))))



(defun get-substrate-edge-assertions (&key abox type-of-substrate)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "get-substrate-edge-assertions"
      (mapcar #'transform-s-expr (list abox abox type-of-substrate type-of-substrate))
      (mapcar #'transform-s-expr nil)))))



(defun get-substrate-edges (&key abox type-of-substrate)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "get-substrate-edges"
      (mapcar #'transform-s-expr (list abox abox type-of-substrate type-of-substrate))
      (mapcar #'transform-s-expr nil)))))



(defun get-substrate-node-assertions (&key abox type-of-substrate)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "get-substrate-node-assertions"
      (mapcar #'transform-s-expr (list abox abox type-of-substrate type-of-substrate))
      (mapcar #'transform-s-expr nil)))))



(defun get-substrate-nodes (&key abox type-of-substrate)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "get-substrate-nodes"
      (mapcar #'transform-s-expr (list abox abox type-of-substrate type-of-substrate))
      (mapcar #'transform-s-expr nil)))))



(defun get-process-pool-size nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "get-process-pool-size"))))

(defun get-maximum-size-of-process-pool nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "get-maximum-size-of-process-pool"))))

(defun get-initial-size-of-process-pool nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "get-initial-size-of-process-pool"))))

(defun set-maximum-size-of-process-pool (n)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "set-maximum-size-of-process-pool"
      (mapcar #'transform-s-expr (list n))
      (mapcar #'transform-s-expr nil)))))



(defun set-initial-size-of-process-pool (n)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "set-initial-size-of-process-pool"
      (mapcar #'transform-s-expr (list n))
      (mapcar #'transform-s-expr nil)))))



(defun set-rewrite-defined-concepts (val)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "set-rewrite-defined-concepts"
      (mapcar #'transform-s-expr (list val))
      (mapcar #'transform-s-expr nil)))))



(defun set-nrql-mode (mode)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "set-nrql-mode"
      (mapcar #'transform-s-expr (list mode))
      (mapcar #'transform-s-expr nil)))))



(defun show-current-qbox (&optional definitions-p)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "show-current-qbox"
      (mapcar #'transform-s-expr (list definitions-p))
      (mapcar #'transform-s-expr nil)))))



(defun get-abox-of-current-qbox nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "get-abox-of-current-qbox"))))

(defun disable-query-realization nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "disable-query-realization"))))

(defun enable-query-realization nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "enable-query-realization"))))

(defun optimizer-dont-use-cardinality-heuristics nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "optimizer-dont-use-cardinality-heuristics"))))

(defun optimizer-use-cardinality-heuristics nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "optimizer-use-cardinality-heuristics"))))

(defun disable-query-optimization nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "disable-query-optimization"))))

(defun enable-query-optimization nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "enable-query-optimization"))))

(defun disable-query-repository nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "disable-query-repository"))))

(defun enable-query-repository nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "enable-query-repository"))))

(defun dont-report-tautological-queries nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "dont-report-tautological-queries"))))

(defun report-tautological-queries nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "report-tautological-queries"))))

(defun dont-report-inconsistent-queries nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "dont-report-inconsistent-queries"))))

(defun report-inconsistent-queries nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "report-inconsistent-queries"))))

(defun describe-query-processing-mode nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "describe-query-processing-mode"))))

(defun describe-current-substrate nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "describe-current-substrate"))))

(defun include-permutations nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "include-permutations"))))

(defun exclude-permutations nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "exclude-permutations"))))

(defun dont-add-rule-consequences-automatically nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "dont-add-rule-consequences-automatically"))))

(defun add-rule-consequences-automatically nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "add-rule-consequences-automatically"))))

(defun process-set-at-a-time nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "process-set-at-a-time"))))

(defun process-tuple-at-a-time nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "process-tuple-at-a-time"))))

(defun get-max-no-of-tuples-bound nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "get-max-no-of-tuples-bound"))))

(defun set-max-no-of-tuples-bound (&optional n)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "set-max-no-of-tuples-bound"
      (mapcar #'transform-s-expr (list n))
      (mapcar #'transform-s-expr nil)))))



(defun dont-check-abox-consistency-before-querying nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "dont-check-abox-consistency-before-querying"))))

(defun check-abox-consistency-before-querying nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "check-abox-consistency-before-querying"))))

(defun enable-lazy-tuple-computation nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "enable-lazy-tuple-computation"))))

(defun enable-eager-tuple-computation nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "enable-eager-tuple-computation"))))

(defun restore-standard-settings nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "restore-standard-settings"))))

(defun dont-add-role-assertions-for-datatype-properties nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "dont-add-role-assertions-for-datatype-properties"))))

(defun add-role-assertions-for-datatype-properties nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "add-role-assertions-for-datatype-properties"))))

(defun disable-told-information-querying nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "disable-told-information-querying"))))

(defun enable-told-information-querying nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "enable-told-information-querying"))))

(defun disable-nrql-warnings nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "disable-nrql-warnings"))))

(defun enable-nrql-warnings nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "enable-nrql-warnings"))))

(defun disable-kb-has-changed-warning-tokens nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "disable-kb-has-changed-warning-tokens"))))

(defun enable-kb-has-changed-warning-tokens nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "enable-kb-has-changed-warning-tokens"))))

(defun disable-phase-two-starts-warning-tokens nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "disable-phase-two-starts-warning-tokens"))))

(defun enable-phase-two-starts-warning-tokens nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "enable-phase-two-starts-warning-tokens"))))

(defun disable-two-phase-query-processing-mode nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "disable-two-phase-query-processing-mode"))))

(defun enable-two-phase-query-processing-mode nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "enable-two-phase-query-processing-mode"))))

(defun disable-abox-mirroring nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "disable-abox-mirroring"))))

(defun enable-very-smart-abox-mirroring nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "enable-very-smart-abox-mirroring"))))

(defun enable-smart-abox-mirroring nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "enable-smart-abox-mirroring"))))

(defun enable-abox-mirroring nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "enable-abox-mirroring"))))

(defun disable-sql-data-substrate-mirroring nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "disable-sql-data-substrate-mirroring"))))

(defun enable-sql-data-substrate-mirroring nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "enable-sql-data-substrate-mirroring"))))

(defun use-$?-prefix-for-una-variables nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "use-$?-prefix-for-una-variables"))))

(defun use-?-prefix-for-una-variables nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "use-?-prefix-for-una-variables"))))

(defun dont-use-individual-synonym-equivalence-classes nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "dont-use-individual-synonym-equivalence-classes"))))

(defun use-individual-synonym-equivalence-classes nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "use-individual-synonym-equivalence-classes"))))

(defun disable-data-substrate-mirroring nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "disable-data-substrate-mirroring"))))

(defun enable-data-substrate-mirroring nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "enable-data-substrate-mirroring"))))

(defun wait-for-rules-to-terminate nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "wait-for-rules-to-terminate"))))

(defun wait-for-queries-to-terminate nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "wait-for-queries-to-terminate"))))

(defun describe-all-rules (&optional rewritten-p)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "describe-all-rules"
      (mapcar #'transform-s-expr (list rewritten-p))
      (mapcar #'transform-s-expr nil)))))



(defun describe-all-queries (&optional rewritten-p)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "describe-all-queries"
      (mapcar #'transform-s-expr (list rewritten-p))
      (mapcar #'transform-s-expr nil)))))



(defun get-all-answers (&rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "get-all-answers"
      (mapcar #'transform-s-expr (list))
      (mapcar #'transform-s-expr args)))))



(defun get-answer-size (query &optional execute-p)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "get-answer-size"
      (mapcar #'transform-s-expr (list query execute-p))
      (mapcar #'transform-s-expr nil)))))



(defun run-all-rules (&rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "run-all-rules"
      (mapcar #'transform-s-expr (list))
      (mapcar #'transform-s-expr args)))))



(defun reexecute-all-rules (&rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "reexecute-all-rules"
      (mapcar #'transform-s-expr (list))
      (mapcar #'transform-s-expr args)))))



(defun execute-all-rules (&rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "execute-all-rules"
      (mapcar #'transform-s-expr (list))
      (mapcar #'transform-s-expr args)))))



(defun run-all-queries (&rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "run-all-queries"
      (mapcar #'transform-s-expr (list))
      (mapcar #'transform-s-expr args)))))



(defun reexecute-all-queries (&rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "reexecute-all-queries"
      (mapcar #'transform-s-expr (list))
      (mapcar #'transform-s-expr args)))))



(defun execute-all-queries (&rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "execute-all-queries"
      (mapcar #'transform-s-expr (list))
      (mapcar #'transform-s-expr args)))))



(defun abort-all-rules nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "abort-all-rules"))))

(defun abort-all-queries nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "abort-all-queries"))))

(defun terminated-rules nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "terminated-rules"))))

(defun inactive-rules nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "inactive-rules"))))

(defun processed-rules nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "processed-rules"))))

(defun terminated-queries nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "terminated-queries"))))

(defun inactive-queries nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "inactive-queries"))))

(defun processed-queries nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "processed-queries"))))

(defun waiting-expensive-rules nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "waiting-expensive-rules"))))

(defun waiting-cheap-rules nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "waiting-cheap-rules"))))

(defun waiting-rules nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "waiting-rules"))))

(defun waiting-expensive-queries nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "waiting-expensive-queries"))))

(defun waiting-cheap-queries nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "waiting-cheap-queries"))))

(defun waiting-queries nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "waiting-queries"))))

(defun running-expensive-rules nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "running-expensive-rules"))))

(defun running-cheap-rules nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "running-cheap-rules"))))

(defun running-rules nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "running-rules"))))

(defun running-expensive-queries nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "running-expensive-queries"))))

(defun running-cheap-queries nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "running-cheap-queries"))))

(defun running-queries nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "running-queries"))))

(defun active-expensive-rules nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "active-expensive-rules"))))

(defun active-cheap-rules nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "active-cheap-rules"))))

(defun active-rules nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "active-rules"))))

(defun active-expensive-queries nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "active-expensive-queries"))))

(defun active-cheap-queries nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "active-cheap-queries"))))

(defun active-queries nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "active-queries"))))

(defun prepared-rules nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "prepared-rules"))))

(defun ready-rules nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "ready-rules"))))

(defun prepared-queries nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "prepared-queries"))))

(defun ready-queries nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "ready-queries"))))

(defun expensive-rules nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "expensive-rules"))))

(defun cheap-rules nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "cheap-rules"))))

(defun inaccurate-rules nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "inaccurate-rules"))))

(defun accurate-rules nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "accurate-rules"))))

(defun all-rules nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "all-rules"))))

(defun expensive-queries nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "expensive-queries"))))

(defun cheap-queries nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "cheap-queries"))))

(defun inaccurate-queries nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "inaccurate-queries"))))

(defun accurate-queries nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "accurate-queries"))))

(defun all-queries nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "all-queries"))))

(defun describe-all-definitions (&key tbox)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "describe-all-definitions"
      (mapcar #'transform-s-expr (list tbox tbox))
      (mapcar #'transform-s-expr nil)))))



(defun describe-definition (name &key tbox)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "describe-definition"
      (mapcar #'transform-s-expr (list name tbox tbox))
      (mapcar #'transform-s-expr nil)))))



(defun delete-all-definitions (&key tbox)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "delete-all-definitions"
      (mapcar #'transform-s-expr (list tbox tbox))
      (mapcar #'transform-s-expr nil)))))



(defun undefine-query (name &key tbox)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "undefine-query"
      (mapcar #'transform-s-expr (list name tbox tbox))
      (mapcar #'transform-s-expr nil)))))



(defun define-and-prepare-query (name head body &rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "define-and-prepare-query"
      (mapcar #'transform-s-expr (list name head body))
      (mapcar #'transform-s-expr args)))))



(defun define-and-execute-query (name head body &rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "define-and-execute-query"
      (mapcar #'transform-s-expr (list name head body))
      (mapcar #'transform-s-expr args)))))



(defun define-query (name head body &rest args &key keep-p tbox &allow-other-keys)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "define-query"
      (mapcar #'transform-s-expr (list name head body keep-p keep-p tbox tbox))
      (mapcar #'transform-s-expr args)))))



(defun racer-prepare-tbox-query (res-args query &rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "racer-prepare-tbox-query"
      (mapcar #'transform-s-expr (list res-args query))
      (mapcar #'transform-s-expr args)))))



(defun racer-answer-tbox-query1 (query res-args &rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "racer-answer-tbox-query1"
      (mapcar #'transform-s-expr (list query res-args))
      (mapcar #'transform-s-expr args)))))



(defun racer-answer-tbox-query (res-args query &rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "racer-answer-tbox-query"
      (mapcar #'transform-s-expr (list res-args query))
      (mapcar #'transform-s-expr args)))))



(defun racer-prepare-rule (query res-args &rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "racer-prepare-rule"
      (mapcar #'transform-s-expr (list query res-args))
      (mapcar #'transform-s-expr args)))))



(defun racer-apply-rule (query res-args &rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "racer-apply-rule"
      (mapcar #'transform-s-expr (list query res-args))
      (mapcar #'transform-s-expr args)))))



(defun prepare-nrql-engine (abox &rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "prepare-nrql-engine"
      (mapcar #'transform-s-expr (list abox))
      (mapcar #'transform-s-expr args)))))



(defun racer-prepare-query (res-args query &rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "racer-prepare-query"
      (mapcar #'transform-s-expr (list res-args query))
      (mapcar #'transform-s-expr args)))))



(defun racer-answer-query-under-premise (premise res-args query &rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "racer-answer-query-under-premise"
      (mapcar #'transform-s-expr (list premise res-args query))
      (mapcar #'transform-s-expr args)))))



(defun racer-answer-query1 (query res-args &rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "racer-answer-query1"
      (mapcar #'transform-s-expr (list query res-args))
      (mapcar #'transform-s-expr args)))))



(defun racer-answer-query (res-args query &rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "racer-answer-query"
      (mapcar #'transform-s-expr (list res-args query))
      (mapcar #'transform-s-expr args)))))



(defun full-reset nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "full-reset"))))

(defun reset-nrql-engine (&key full-reset-p)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "reset-nrql-engine"
      (mapcar #'transform-s-expr (list full-reset-p full-reset-p))
      (mapcar #'transform-s-expr nil)))))



(defun reset-all-substrates nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "reset-all-substrates"))))

(defun delete-all-rules nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "delete-all-rules"))))

(defun delete-all-queries nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "delete-all-queries"))))

(defun describe-rule (query &optional rewritten-p)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "describe-rule"
      (mapcar #'transform-s-expr (list query rewritten-p))
      (mapcar #'transform-s-expr nil)))))



(defun describe-query (query &optional rewritten-p)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "describe-query"
      (mapcar #'transform-s-expr (list query rewritten-p))
      (mapcar #'transform-s-expr nil)))))



(defun get-dag-of-qbox-for-abox (substrate &optional type-of-substrate)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "get-dag-of-qbox-for-abox"
      (mapcar #'transform-s-expr (list substrate type-of-substrate))
      (mapcar #'transform-s-expr nil)))))



(defun show-qbox-for-abox (abox &optional definitions-p type-of-substrate)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "show-qbox-for-abox"
      (mapcar #'transform-s-expr (list abox definitions-p type-of-substrate))
      (mapcar #'transform-s-expr nil)))))



(defun get-nodes-in-qbox-for-abox (abox &optional type-of-substrate)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "get-nodes-in-qbox-for-abox"
      (mapcar #'transform-s-expr (list abox type-of-substrate))
      (mapcar #'transform-s-expr nil)))))



(defun get-nodes-in-current-qbox nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "get-nodes-in-current-qbox"))))

(defun get-dag-of-current-qbox nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "get-dag-of-current-qbox"))))

(defun query-equivalents (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "query-equivalents"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun query-descendants (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "query-descendants"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun query-children (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "query-children"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun query-ancestors (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "query-ancestors"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun query-parents (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "query-parents"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun query-equivalent-p (a b &rest args &key &allow-other-keys)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "query-equivalent-p"
      (mapcar #'transform-s-expr (list a b))
      (mapcar #'transform-s-expr args)))))



(defun query-entails-p (a b &rest args &key &allow-other-keys)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "query-entails-p"
      (mapcar #'transform-s-expr (list a b))
      (mapcar #'transform-s-expr args)))))



(defun classify-query (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "classify-query"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun query-tautological-p (query &key &allow-other-keys)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "query-tautological-p"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun query-inconsistent-p (query &key &allow-other-keys)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "query-inconsistent-p"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun query-consistent-p (query &key &allow-other-keys)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "query-consistent-p"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun abort-rule (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "abort-rule"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun abort-query (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "abort-query"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun original-rule-body (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "original-rule-body"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun original-query-body (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "original-query-body"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun rule-body (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "rule-body"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun query-body (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "query-body"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun original-rule-head (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "original-rule-head"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun original-query-head (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "original-query-head"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun rule-head (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "rule-head"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun query-head (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "query-head"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun rule-accurate-p (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "rule-accurate-p"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun query-accurate-p (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "query-accurate-p"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun get-answer (query &rest args &key &allow-other-keys)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "get-answer"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr args)))))



(defun get-all-remaining-sets-of-rule-consequences (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "get-all-remaining-sets-of-rule-consequences"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun get-all-remaining-tuples (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "get-all-remaining-tuples"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun get-next-n-remaining-sets-of-rule-consequences (query &optional n)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "get-next-n-remaining-sets-of-rule-consequences"
      (mapcar #'transform-s-expr (list query n))
      (mapcar #'transform-s-expr nil)))))



(defun get-next-n-remaining-tuples (query &optional n)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "get-next-n-remaining-tuples"
      (mapcar #'transform-s-expr (list query n))
      (mapcar #'transform-s-expr nil)))))



(defun describe-rule-status (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "describe-rule-status"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun describe-query-status (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "describe-query-status"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun rule-inactive-p (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "rule-inactive-p"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun rule-processed-p (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "rule-processed-p"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun query-inactive-p (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "query-inactive-p"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun query-processed-p (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "query-processed-p"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun active-expensive-rule-p (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "active-expensive-rule-p"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun active-expensive-query-p (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "active-expensive-query-p"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun cheap-rule-p (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "cheap-rule-p"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun cheap-query-p (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "cheap-query-p"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun rule-active-p (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "rule-active-p"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun query-active-p (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "query-active-p"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun rule-waiting-p (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "rule-waiting-p"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun query-waiting-p (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "query-waiting-p"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun execute-applicable-rules nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "execute-applicable-rules"))))

(defun unapplicable-rules nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "unapplicable-rules"))))

(defun applicable-rules nil
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A)" "applicable-rules"))))

(defun add-chosen-sets-of-rule-consequences (query &rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "add-chosen-sets-of-rule-consequences"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr args)))))



(defun choose-current-set-of-rule-consequences (query &rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "choose-current-set-of-rule-consequences"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr args)))))



(defun rule-applicable-p (query &rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "rule-applicable-p"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr args)))))



(defun rule-prepared-p (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "rule-prepared-p"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun query-prepared-p (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "query-prepared-p"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun reexecute-rule (query &rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "reexecute-rule"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr args)))))



(defun reexecute-query (query &rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "reexecute-query"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr args)))))



(defun reprepare-rule (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "reprepare-rule"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun reprepare-query (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "reprepare-query"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun execute-rule (query &rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "execute-rule"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr args)))))



(defun execute-query (query &rest args)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "execute-query"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr args)))))



(defun rule-ready-p (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "rule-ready-p"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun query-ready-p (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "query-ready-p"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun next-set-of-rule-consequences-available-p (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "next-set-of-rule-consequences-available-p"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun next-tuple-available-p (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "next-tuple-available-p"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun get-current-set-of-rule-consequences (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "get-current-set-of-rule-consequences"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun get-next-set-of-rule-consequences (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "get-next-set-of-rule-consequences"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun get-current-tuple (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "get-current-tuple"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun get-next-tuple (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "get-next-tuple"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun delete-rule (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "delete-rule"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defun delete-query (query)
  (with-standard-io-syntax-1
    (service-request
      (format nil "(~A~{ ~S~}~{ ~S~})"
      "delete-query"
      (mapcar #'transform-s-expr (list query))
      (mapcar #'transform-s-expr nil)))))



(defmacro del-rcc-edge (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "del-rcc-edge"
      (mapcar #'transform-s-expr args)))))

(defmacro del-rcc-node (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "del-rcc-node"
      (mapcar #'transform-s-expr args)))))

(defmacro rcc-edge-label (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "rcc-edge-label"
      (mapcar #'transform-s-expr args)))))

(defmacro rcc-node-label (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "rcc-node-label"
      (mapcar #'transform-s-expr args)))))

(defmacro rcc-edge (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "rcc-edge"
      (mapcar #'transform-s-expr args)))))

(defmacro rcc-node (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "rcc-node"
      (mapcar #'transform-s-expr args)))))

(defmacro rcc-related (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "rcc-related"
      (mapcar #'transform-s-expr args)))))

(defmacro rcc-instance (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "rcc-instance"
      (mapcar #'transform-s-expr args)))))

(defmacro rcc-consistent? (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "rcc-consistent?"
      (mapcar #'transform-s-expr args)))))

(defmacro in-rcc-box (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "in-rcc-box"
      (mapcar #'transform-s-expr args)))))

(defmacro in-mirror-data-box (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "in-mirror-data-box"
      (mapcar #'transform-s-expr args)))))

(defmacro description-implies? (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "description-implies?"
      (mapcar #'transform-s-expr args)))))

(defmacro edge-label (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "edge-label"
      (mapcar #'transform-s-expr args)))))

(defmacro node-label (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "node-label"
      (mapcar #'transform-s-expr args)))))

(defmacro del-data-edge (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "del-data-edge"
      (mapcar #'transform-s-expr args)))))

(defmacro del-data-node (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "del-data-node"
      (mapcar #'transform-s-expr args)))))

(defmacro data-edge (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "data-edge"
      (mapcar #'transform-s-expr args)))))

(defmacro data-node (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "data-node"
      (mapcar #'transform-s-expr args)))))

(defmacro in-data-box (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "in-data-box"
      (mapcar #'transform-s-expr args)))))

(defmacro undefquery (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "undefquery"
      (mapcar #'transform-s-expr args)))))

(defmacro def-and-exec-query (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "def-and-exec-query"
      (mapcar #'transform-s-expr args)))))

(defmacro def-and-prep-query (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "def-and-prep-query"
      (mapcar #'transform-s-expr args)))))

(defmacro defquery (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "defquery"
      (mapcar #'transform-s-expr args)))))

(defmacro preprule (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "preprule"
      (mapcar #'transform-s-expr args)))))

(defmacro firerule (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "firerule"
      (mapcar #'transform-s-expr args)))))

(defmacro prepare-abox-rule (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "prepare-abox-rule"
      (mapcar #'transform-s-expr args)))))

(defmacro prepare-tbox-query (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "prepare-tbox-query"
      (mapcar #'transform-s-expr args)))))

(defmacro prepare-abox-query (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "prepare-abox-query"
      (mapcar #'transform-s-expr args)))))

(defmacro apply-abox-rule (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "apply-abox-rule"
      (mapcar #'transform-s-expr args)))))

(defmacro tbox-retrieve1 (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "tbox-retrieve1"
      (mapcar #'transform-s-expr args)))))

(defmacro tbox-retrieve (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "tbox-retrieve"
      (mapcar #'transform-s-expr args)))))

(defmacro retrieve-under-premise (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "retrieve-under-premise"
      (mapcar #'transform-s-expr args)))))

(defmacro retrieve1 (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "retrieve1"
      (mapcar #'transform-s-expr args)))))

(defmacro retrieve (&rest args)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A~{ ~A~})"
      "retrieve"
      (mapcar #'transform-s-expr args)))))

(defmacro with-nrql-settings ((&rest args) &body body)
  (with-standard-io-syntax-1
    `(service-request
      ,(format nil "(~A (~{ ~S~})~{ ~S~})"
      "with-nrql-settings"
      (mapcar #'transform-s-expr args)
      (mapcar #'transform-s-expr body)))))
