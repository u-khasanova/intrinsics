# Intrinsics Demo: _mm256_div_ps

## Project Overview
This project demonstrates the use of the AVX2 SIMD instruction `_mm256_div_ps` for vectorized floating-point division.

## Technical Details

### Instruction Selection
Based on student ID **61**:
- **Prefix**: `_mm256` (61 % 2 = 1)
- **Middle**: `_div` (61 ÷ 8 = 7)
- **Suffix**: `_ps` (61 % 4 = 1)

**Final instruction**: `_mm256_div_ps`

## Project Structure
```
intrinsics/
├── src/
│   └── demo_mm256_div_ps.cpp    # Main demonstration program
├── Makefile                     # Build configuration
└── README.md                    # This documentation
```

### Compilation
```bash
make
```

### Execution
```bash
make run
```

### Cleanup
```bash
make clean
```
