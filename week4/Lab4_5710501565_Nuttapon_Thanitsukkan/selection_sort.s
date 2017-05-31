        .text
        .globl        main
main:
        addi        $sp, $sp, -412      
                                        
                                        
        sw      $ra, 408($sp)           
        sw      $s0, 404($sp)           
        sw      $s1, 400($sp)           
        move    $s0, $sp                

        li        $v0, 5                
        syscall                         
        move    $s1, $v0                
                                        

        move    $a0, $s0                
        move    $a1, $s1                
        jal     rd_lst

        
        move    $a0, $s0                
        move    $a1, $s1                
        jal     selsrt


        move    $a0, $s0                
        move    $a1, $s1                
        jal     pr_lst

        
        lw      $ra, 408($sp)
        lw      $s0, 404($sp)
        lw      $s1, 400($sp)
        addi    $sp, $sp, 412
        

        li      $v0, 10
        syscall



rd_lst: 

        addi    $sp, $sp, -4            
        sw      $ra, 0($sp)             

        
        move    $t0, $zero              
rd_tst: bge     $t0, $a1, rddone        
                                        
                                        
        li      $v0, 5                  
        syscall                         
        sll     $t1, $t0, 2             
        add     $t1, $a0, $t1           
        sw      $v0, 0($t1)             
                                        
        addi    $t0, $t0, 1             
        j       rd_tst                  
        
rddone: lw      $ra, 0($sp)             
        addi    $sp, $sp 4              
        jr      $ra                     


pr_lst: 
        addi    $sp, $sp, -4
        sw      $ra, 0($sp) 

        move    $t2, $a0                
        move    $t0, $zero              
pr_tst: bge     $t0, $a1, prdone        
        sll     $t1, $t0, 2             
        add     $t1, $t2, $t1           
        lw      $a0, 0($t1)             
        li      $v0, 1                  
        syscall

        la      $a0, space              
        li      $v0, 4                  
        syscall

        addi    $t0, $t0, 1             
        j       pr_tst                  
        
prdone: 
        la      $a0, newln
        li      $v0, 4                  
        syscall

        lw      $ra, 0($sp)             
        addi    $sp, $sp 4              
        jr      $ra                     


selsrt:
        addi    $sp, $sp, -24
        sw      $ra, 20($sp) 
        sw      $s0, 16($sp) 
        sw      $s1, 12($sp) 
        sw      $s2,  8($sp) 
        sw      $s3,  4($sp) 
        sw      $s4,  0($sp) 

        move    $s0, $a0                
        move    $s1, $a1                

        addi    $s3, $s1, -1            
        move    $s2, $zero              
lp_tst: bge     $s2, $s3, lpdone        
                                        
        move    $a0, $s0                
        move    $a1, $s2                
        move    $a2, $s3                
        jal     locmin                  
        move    $s4, $v0                

        move    $a0, $s0                
        move    $a1, $s2                
        move    $a2, $s4                
                                        
        jal     swap                    

        addi    $s2, $s2, 1             
        j       lp_tst                  
        
lpdone: lw      $ra, 20($sp)
        lw      $s0, 16($sp)
        lw      $s1, 12($sp)
        lw      $s2,  8($sp)
        lw      $s3,  4($sp)
        lw      $s4,  0($sp)
        addi    $sp, $sp, 24
        jr      $ra         

locmin:
        move    $t0, $a1                
                                        
        sll     $t3, $t0, 2             
        addu    $t3, $t3, $a0           
        lw      $t5, 0($t3)             

        addi    $t1, $a1, 1
lm_lp:  bgt     $t1, $a2, lmdone
        sll     $t2, $t1, 2     
        addu    $t2, $a0, $t2   
        lw      $t4, 0($t2)     
        bge     $t4, $t5, no_chg
                                
        move    $t0, $t1        
        move    $t5, $t4        
                                

no_chg: addi    $t1, $t1, 1     
        j       lm_lp

lmdone: move    $v0 $t0         
        jr      $ra             

swap:
        sll     $t0, $a1, 2
        add     $t0, $a0, $t0
        lw      $t1, 0($t0)  

        sll     $t2, $a2, 2
        add     $t2, $a0, $t2
        lw      $t3, 0($t2)  

        sw      $t1, 0($t2)
        sw      $t3, 0($t0)

        jr      $ra

        .data
space:  .asciiz " "
newln:  .asciiz "\n"