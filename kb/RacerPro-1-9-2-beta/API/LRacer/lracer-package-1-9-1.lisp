(in-package cl-user)

#+:mcl
(eval-when (:compile-toplevel :load-toplevel :execute)
  (require :opentransport))

#+:lispworks
(eval-when (:compile-toplevel :load-toplevel :execute)
  (require "comm"))

(defpackage racer
  (:use common-lisp :nrql-symbols #+:allegro :excl)
  (:export #:+top-symbol+
	   #:+bottom-symbol+
	   #:tbox
	   #:init-tbox
	   #:save-tbox
	   #:delete-tbox
	   #:forget-tbox
	   #:current-tbox
	   #:set-nominals-disjoint-p
	   #:nominals-disjoint-p
	   #:find-tbox
	   #:set-find-tbox
	   #:create-tbox-clone
	   #:clone-tbox
	   #:tbox-name
	   #:in-tbox
	   #:init-abox
	   #:set-current-tbox
	   #:set-current-abox
	   #:save-abox
	   #:delete-abox
	   #:forget-abox
	   #:current-abox
	   #:find-abox
	   #:set-find-abox
	   #:create-abox-clone
	   #:clone-abox
	   #:abox-name
	   #:in-abox
	   #:*top*
	   #:top
	   #:*bottom*
	   #:bottom
	   #:at-least
	   #:at-most
	   #:exactly
	   #:some
	   #:all
	   #:not
	   #:and
	   #:or
	   #:inv
	   #:define-tbox
	   #:signature
	   #:ensure-tbox-signature
	   #:ensure-abox-signature
	   #:get-kb-signature
	   #:get-tbox-signature
	   #:get-abox-signature
	   #:in-knowledge-base
	   #:define-primitive-concept
	   #:defprimconcept
	   #:define-concept
	   #:defconcept
	   #:implies
	   #:equivalent
	   #:disjoint
	   #:define-disjoint-primitive-concept
	   #:add-disjointness-axiom
	   #:add-concept-axiom
	   #:forget-concept-axiom
	   #:forget-role-axioms
	   #:forget-constraint
	   #:forget-constrained-assertion
	   #:forget-disjointness-axiom
	   #:forget-disjointness-axiom-statement
	   #:define-primitive-role
	   #:defprimrole
	   #:define-primitive-attribute
	   #:defprimattribute
	   #:defcdattribute
	   #:define-concrete-domain-attribute
	   #:add-role-axioms
					;add-role-axiom ;now obsolete?
	   #:define-distinct-individual
	   #:define-individual
	   #:add-individual
	   #:state
	   #:instance
	   #:related
	   #:add-concept-assertion
	   #:add-role-assertion
	   #:forget-concept-assertion
	   #:forget-role-assertion
	   #:forget
	   #:forget-statement
	   #:concept-satisfiable?
	   #:concept-satisfiable-p
	   #:alc-concept-coherent
	   #:concept-subsumes?
	   #:concept-subsumes-p
	   #:concept-equivalent?
	   #:concept-equivalent-p
	   #:concept-disjoint?
	   #:concept-disjoint-p
	   #:classify-tbox
	   #:check-tbox-coherence
	   #:tbox-coherent-p
	   #:tbox-coherent?
	   #:tbox-classified-p
	   #:tbox-classified?
	   #:tbox-prepared-p
	   #:tbox-prepared?
	   #:tbox-cyclic-p
	   #:tbox-cyclic?
	   #:cyclic-concepts-in-tbox
	   #:atomic-concept-descendants
	   #:atomic-concept-ancestors
	   #:atomic-concept-children
	   #:atomic-concept-parents
	   #:atomic-concept-synonyms
	   #:concept-synonyms
	   #:concept-descendants
	   #:concept-offspring
	   #:concept-children
	   #:concept-ancestors
	   #:concept-parents
	   #:concept-is-primitive-p
	   #:concept-is-primitive?
	   #:concept-instances
	   #:taxonomy
	   #:role-parents
	   #:role-children
	   #:role-offspring
	   #:role-ancestors
	   #:role-descendants
	   #:role-inverse
	   #:atomic-role-parents
	   #:atomic-role-children
	   #:atomic-role-ancestors
	   #:atomic-role-descendants
	   #:atomic-role-inverse
	   #:define-abox
	   #:realize-abox
	   #:check-abox-coherence
	   #:abox-realized-p
	   #:abox-realized?
	   #:abox-prepared-p
	   #:abox-prepared?
	   #:abox-consistent-p
	   #:abox-consistent?
	   #:abox-una-consistent-p
	   #:abox-una-consistent?
	   #:role-subsumes?
	   #:role-subsumes-p
	   #:individual-p
	   #:individual?
	   #:cd-object-p
	   #:cd-object?
	   #:individual-types
	   #:individual-direct-types
	   #:individual-instance?
	   #:individual-instance-p
	   #:individual-fillers
	   #:individual-attribute-fillers
	   #:individuals-related?
	   #:individuals-related-p
	   #:individuals-equal?
	   #:individuals-not-equal?
	   #:individuals-equal-p
	   #:individuals-not-equal-p
	   #:instantiators
	   #:most-specific-instantiators
	   #:retrieve-concept-instances
	   #:retrieve-individual-filled-roles
	   #:individual-filled-roles
	   #:retrieve-direct-predecessors
	   #:direct-predecessors
	   #:retrieve-related-individuals
	   #:retrieve-individual-fillers
	   #:retrieve-individual-attribute-fillers
	   #:told-value
	   #:related-individuals
	   #:all-tboxes
	   #:delete-all-tboxes
	   #:all-aboxes
	   #:delete-all-aboxes
	   #:loop-over-aboxes
	   #:loop-over-tboxes
	   #:all-roles
	   #:all-features
	   #:all-transitive-roles
	   #:all-attributes
	   #:attribute-type
	   #:attribute-has-range
	   #:attribute-domain
	   #:attribute-domain-1
	   #:attribute-has-domain
	   #:all-atomic-concepts
	   #:all-equivalent-concepts
	   #:all-individuals
	   #:all-concept-assertions-for-individual
	   #:all-role-assertions-for-individual-in-domain
	   #:all-role-assertions-for-individual-in-range
	   #:all-role-assertions
	   #:all-attribute-assertions
	   #:all-concept-assertions
	   #:all-constraints
	   #:role-p
	   #:role?
	   #:transitive-p
	   #:transitive?
	   #:feature-p
	   #:feature?
	   #:cd-attribute-p
	   #:cd-attribute?
	   #:symmetric-p
	   #:symmetric?
	   #:reflexive-p
	   #:reflexive?
	   #:concept-p
	   #:concept?
	   #:describe-tbox
	   #:describe-concept
	   #:describe-role
	   #:describe-abox
	   #:describe-individual
	   #:alc-concept-coherent
	   #:validate-true
	   #:validate-false
	   #:validate-set
	   #:verify-with-concept-tree-list
	   #:verify-with-abox-individuals-list
	   #:verify-with-concept-tree
	   #:test-assert
	   #:test-verify-with-concept-tree-list
	   #:test-verify-with-abox-individuals-list
	   #:display-graph
	   #:print-tbox-tree
	   #:with-racer-statistics
	   #:with-sat-statistics
	   #:with-kb-statistics
	   #:with-verbose-statistics
	   #:constrained
	   #:add-attribute-assertion
	   #:constraints
	   #:add-constraint-assertion
	   #:>=
	   #:<=
	   #:>
	   #:<
	   #:<>
	   #:=
	   #:*
	   #:+
	   #:-
	   #:a
	   #:an
	   #:no
	   #:ensure
	   #:min
	   #:max
	   #:range
	   #:equal
	   #:string=
	   #:string<>
	   #:complex
	   #:real
	   #:integer
	   #:cardinal
	   #:string
	   #:boolean
	   #:xml-read-tbox-file
	   #:rdfs-read-tbox-file
	   #:racer-read-file
	   #:racer-read-document
	   #:daml-read-file
	   #:daml-read-document
	   #:owl-read-file
	   #:owl-read-document
	   #:dig-read-file
	   #:dig-read-document
	   #:associated-tbox
	   #:set-associated-tbox
	   #:associated-aboxes
	   #:save-kb
	   #:include-kb
	   #:import-kb
	   #:clear-default-tbox
	   #:compute-index-for-instance-retrieval
	   #:ensure-subsumption-based-query-answering
	   #:ensure-small-tboxes
	   #:publish
	   #:publish-1
	   #:unpublish
	   #:unpublish-1
	   #:subscribe
	   #:subscribe-1
	   #:unsubscribe
	   #:unsubscribe-1
	   #:init-subscriptions
	   #:init-subscriptions-1
	   #:init-publications
	   #:init-publications-1
	   #:check-subscriptions
	   #:functional
	   #:role-is-functional
	   #:transitive
	   #:role-is-transitive
	   #:inverse
	   #:inverse-of-role
	   #:declare-disjoint
	   #:domain
	   #:role-has-domain
	   ;;range
	   #:role-has-range
	   #:implies-role
	   #:role-has-parent
	   #:get-tbox-language
	   #:get-abox-language
	   #:get-meta-constraint
	   #:get-concept-definition
	   #:get-concept-negated-definition
	   #:get-concept-definition-1
	   #:get-concept-negated-definition-1
	   #:atomic-role-range
	   #:role-range
	   #:atomic-role-domain
	   #:role-domain
	   #:default
	   #:logging-on
	   #:logging-off
	   #:tbox-namespaces
	   #:remove-prefix
	   #:get-namespace-prefix
	   #:expt
	   #:store-tbox-image
	   #:store-tboxes-image
	   #:store-abox-image
	   #:store-aboxes-image
	   #:store-kb-image
	   #:store-kbs-image
	   #:restore-abox-image
	   #:restore-aboxes-image
	   #:restore-tbox-image
	   #:restore-tboxes-image
	   #:restore-kb-image
	   #:restore-kbs-image
	   #:mirror
	   #:clear-mirror-table
	   #:kb-ontologies
	   #:compute-implicit-role-fillers
	   #:compute-all-implicit-role-fillers
	   #:constraint-entailed-p
	   #:constraint-entailed?
	   #:roles-equivalent
	   #:roles-equivalent-1
	   #:role-equivalent-p
	   #:role-equivalent?
	   #:atomic-role-synonyms
	   #:role-synonyms
	   #:print-abox-individuals
	   #:individual-told-datatype-fillers
	   #:retrieve-individual-told-datatype-fillers
	   #:role-used-as-datatype-property-p
	   #:role-is-used-as-datatype-property
	   #:datatype-role-range
	   #:datatype-role-has-range
	   #:set-server-timeout
	   #:get-server-timeout
	   #:define-datatype-property
	   #:add-datatype-property
	   #:with-unique-name-assumption
	   #:without-unique-name-assumption
	   #:set-unique-name-assumption
	   #:retrieve-individual-synonyms
	   #:individual-synonyms

               
	   #:attribute-filler
	   #:set-attribute-filler
	   #:datatype-role-filler
	   #:add-datatype-role-filler
                  

	   #:get-tbox-version
	   #:get-abox-version

	   #:individual-attribute-value
	   #:retrieve-individual-attribute-value
	   #:create-tbox-internal-marker-concept

	   #:parse-expression

	   #:role-used-as-annotation-property-p
	   #:role-is-used-as-annotation-property
	   #:add-annotation-concept-assertion
	   #:add-annotation-role-assertion
	   #:all-annotation-concept-assertions
	   #:all-annotation-role-assertions

	   #:true?
	   #:false?

	   #:create-tbox-internal-marker-concept

	   #:racer-internal%has-string-value
	   #:racer-internal%has-integer-value
	   #:racer-internal%has-cardinal-value
	   #:racer-internal%has-real-value
	   #:racer-internal%has-boolean-value

	   #:internal-individuals-related-p
	   #:swrl-forward-chaining
	   #:prepare-racer-engine
	   #:set-rewrite-defined-concepts
	   #:enable-optimized-query-processing
	   #:prepare-abox
	   
	   #:same-as 
	   #:same-individual-as
	   #:add-same-individual-as-assertion
	   #:different-from
	   #:add-different-from-assertion
	   #:all-different
	   #:add-all-different-assertion
	   
	   #:declare-current-knowledge-bases-as-persistent
	   
	   #:triple-store-read-file
	   #:use-triple-store
	   #:materialize-inferences
	   #:pracer-answer-query
	   #:pretrieve
	   #:triple-store-open-p
	   #:close-triple-store
	   #:open-triple-store
	   #:create-triple-store
	   #:index-all-triples

	   #:server-case
           
           #:define-event-assertion 
           #:add-event-assertion
           #:define-event-rule
           #:add-event-rule
           #:timenet-retrieve
           #:timenet-answer-query

           #:enable-abduction 
           #:disable-abduction 
           #:racer-answer-query-with-explanation
           #:retrieve-with-explanation

           #:get-role-datatype
           #:define-rule
           #:add-rule-axiom
	   #:sparql-answer-query
	   #:sparql-retrieve
	   
	   #:without-signature-checks

	   #:with-critical-section
                  
	   #:with-server-connection
	   #:*default-racer-host*
	   #:*default-racer-tcp-port*
	   #:*verbose-connection*
	   #:*with-server-connection*
	   #:*service-request-verbose*
	   #:open-server-connection
	   #:reopen-server-connection
	   #:close-server-connection
	   
	   #:test-with-timeout
	   #:test-verify-with-abox-individuals-list
	   #:test-assert
	   #:with-timeout

           #:lcs-unfold
           #:lcs
           #:msc-k
           #:forget-individual
	   #:add-prefix
	   #:define-prefix))

(eval-when (:load-toplevel :execute)
  (defun use-racer-in-cl-user ()
    (dolist (package '(racer nrql-symbols))
      (loop for sym being the external-symbols of (find-package package) do
          (let ((cl-user-sym (find-symbol (symbol-name sym) 'cl-user)))
            (when cl-user-sym
              (unintern cl-user-sym 'cl-user)))
          (import sym 'cl-user)))))

(eval-when (:load-toplevel :execute)
  (use-racer-in-cl-user))


(defpackage racer-user
  (:use common-lisp racer))



