.data
msg:
    .string "Hello, World!"


.text

main:
    li a0, 1
    la a1, msg
    li a2, (. - msg) # 长度 = 字符串结束的位置 (点号 .) 减去字符串开始的位置 (msg)

    