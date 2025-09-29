# 假设 t0 = 5, t1 = 5
    
    beq t0, t1, equal_path # 如果 t0 == t1，跳转到 equal_path
    
    # --- else 分支 ---
    li t2, 0             # 如果不相等，执行这里：将 0 存入 t2
    j end_if             # 无条件跳转，跳过 equal_path 分支
    
equal_path:
    # --- if 分支 ---
    li t2, 1             # 如果相等，执行这里：将 1 存入 t2
    
end_if:
    # ... 程序继续执行