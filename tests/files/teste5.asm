            section data
one:        CONS  1
two:        CONST -2
result:     SPACE
start:      SPACE

; Simple error testing
            section text
start:      ad      one                 ; Simple add something
            aDd     two
            STORE   result
            Jmp     end
; Let's finish this empty file
end:        stop
