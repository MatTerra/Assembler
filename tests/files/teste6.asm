            section data
one:
            CONST 1
two:
            CONST -2
result:
            SPACE

            section text
start:
            adD     one                 ; Simple add something
            aDd     two
            STORE   result
            Jmp     end
; Let's finish this useless file
end:        stop
