.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
read:
	li $v0, 4
	la $a0, _prompt
	syscall
	li $v0, 5
	syscall
	jr $ra

write:
	li $v0, 1
	syscall
	li $v0, 4
	la $a0, _ret
	syscall
	move $v0, $0
	jr $ra

sort:
	addi $sp, $sp, -64
	sw $ra, 60($sp)
	sw $fp, 56($sp)
	addi $fp, $sp, 64
	sw $t0, 0($sp)
	li $t1, 0
	move $t2, $t1
	li $t3, 0
	move $t4, $t3
label1:
	blt $t2, $a0, label2
	j label3
label2:
	li $t6, 4
	mul $t5, $t2, $t6
	add $t6, $t5, $sp
	li $t8, 2
	mul $t7, $t2, $t8
	li $t9, 100
	sub $t8, $t9, $t7
	sw $t8, 0($t6)
	addi $t9, $t2, 1
	move $t2, $t9
	j label1
label3:
	li $t1, 0
	move $t2, $t1
label4:
	blt $t2, $a0, label5
	j label6
label5:
	li $t3, 0
	move $t4, $t3
label7:
	blt $t4, $t2, label8
	j label9
label8:
	li $t6, 4
	mul $t5, $t2, $t6
	add $t6, $t5, $sp
	li $t8, 4
	mul $t7, $t4, $t8
	add $t8, $t7, $sp
	lw $t9, 0($t6)
	lw $t1, 0($t8)
	blt $t9, $t1, label10
	j label11
label10:
	li $t3, 4
	mul $t1, $t2, $t3
	add $t3, $t1, $sp
	lw $t5, 0($t3)
	li $t7, 4
	mul $t6, $t2, $t7
	add $t7, $t6, $sp
	li $t8, 4
	mul $t8, $t4, $t8
	add $t8, $t9, $sp
	lw $t1, 0($t8)
	sw $t1, 0($t3)
	li $t6, 4
	mul $t3, $t4, $t6
	add $t6, $t3, $sp
	move $t7, $t5
	sw $t7, 0($t6)
label11:
	addi $t8, $t4, 1
	move $t4, $t8
	j label7
label9:
	addi $t9, $t2, 1
	move $t2, $t9
	j label4
label6:
	li $t1, 0
	move $t2, $t1
label12:
	blt $t2, $a0, label13
	j label14
label13:
	li $t6, 4
	mul $t3, $t2, $t6
	add $t6, $t3, $sp
	lw $t7, 0($t6)
	move $a0, $t7
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	jal write
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	addi $t8, $t2, 1
	move $t2, $t8
	j label12
label14:
	lw $ra, 60($sp)
	lw $fp, 56($sp)
	addi $sp, $sp, 64
	move $v0, $zero
	jr $ra

main:
	addi $sp, $sp, -64
	sw $ra, 60($sp)
	sw $fp, 56($sp)
	addi $fp, $sp, 64
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	jal read
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	move $t9, $v0
	li $t9, 100
	bge $t9, $t9, label15
	j label16
label15:
	li $a0, -1
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	jal write
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	j label17
label16:
	addi $sp, $sp, 0
	addi $sp, $sp, -28
	sw $a0, 0($sp)
	sw $t0, 4($sp)
	sw $t2, 8($sp)
	sw $t4, 12($sp)
	sw $t5, 16($sp)
	sw $t9, 20($sp)
	sw $ra, 24($sp)
	move $a0, $t9
	jal sort
	move $t1, $v0
	lw $a0, 0($sp)
	lw $t0, 4($sp)
	lw $t2, 8($sp)
	lw $t4, 12($sp)
	lw $t5, 16($sp)
	lw $t9, 20($sp)
	lw $ra, 24($sp)
	addi $sp, $sp, 28
label17:
	lw $ra, 60($sp)
	lw $fp, 56($sp)
	addi $sp, $sp, 64
	move $v0, $zero
	jr $ra
