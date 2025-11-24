# BÀI 2 - MỞ RỘNG SCANNER CHO NGÔN NGỮ KPL

## CÁC TÍNH NĂNG MỚI ĐÃ BỔ SUNG

### 1. Kiểu dữ liệu mới
- **STRING**: Kiểu dữ liệu chuỗi ký tự (keyword: `STRING`)
- **BYTES**: Kiểu dữ liệu bytes (keyword: `BYTES`)
- **String literal**: Hằng chuỗi được đặt trong dấu ngoặc kép `"..."`, ví dụ: `"Hello World"`

### 2. Phép toán mới
- **Modulo (%)**: Phép lấy phần dư, ví dụ: `10 % 3` → kết quả là 1
- **Power (**)**: Phép lấy mũ, ví dụ: `2 ** 10` → kết quả là 2^10 = 1024

### 3. Comment mới
- **Line comment (//)**: Comment đến cuối dòng (giống C++), ví dụ:
  ```
  x := 10;  // This is a comment
  ```
- Comment cũ `(* ... *)` vẫn hoạt động bình thường

### 4. Cấu trúc lệnh mới
- **REPEAT...UNTIL**: Vòng lặp kiểu repeat-until
  ```
  REPEAT
    <statements>
  UNTIL <condition>;
  ```

## CÁCH BIÊN DỊCH VÀ CHẠY

### Bước 1: Di chuyển vào thư mục bai2
```powershell
cd Bai2\bai2\incompleted
```

### Bước 2: Biên dịch chương trình scanner
```powershell
mingw32-make
```

Nếu không có lỗi, file thực thi `scanner.exe` sẽ được tạo ra.

### Bước 3: Chạy scanner với file test
```powershell
# Test tổng hợp
.\scanner ..\test\example8.kpl

# Test từng tính năng riêng
.\scanner ..\test\test_string.kpl
.\scanner ..\test\test_modulo.kpl
.\scanner ..\test\test_power.kpl
.\scanner ..\test\test_comment.kpl
.\scanner ..\test\test_repeat.kpl
.\scanner ..\test\test_all_features.kpl
```

## CÁCH KIỂM TRA KẾT QUẢ

### 1. Kiểm tra từ khóa mới
Khi chạy `.\scanner ..\test\example8.kpl`, sẽ thấy:
- `KW_STRING` - từ khóa STRING được nhận diện
- `KW_BYTES` - từ khóa BYTES được nhận diện  
- `KW_REPEAT` - từ khóa REPEAT được nhận diện
- `KW_UNTIL` - từ khóa UNTIL được nhận diện

### 2. Kiểm tra string literal
Dòng `msg := "Hello World";` sẽ tạo ra token:
```
TK_STRING("Hello World")
```

### 3. Kiểm tra phép toán modulo (%)
Dòng `result := x % y;` sẽ có token:
```
SB_PERCENT
```

### 4. Kiểm tra phép toán power (**)
Dòng `result := 2 ** 10;` sẽ có token:
```
SB_POWER
```

### 5. Kiểm tra line comment (//)
Dòng có `// This is a line comment` sẽ bị bỏ qua hoàn toàn, không tạo token.

### 6. Kiểm tra cấu trúc REPEAT...UNTIL
```
REPEAT
  ...
UNTIL x >= 100;
```
Sẽ tạo ra các token:
- `KW_REPEAT`
- ... (statements)
- `KW_UNTIL`
- condition tokens
- `SB_SEMICOLON`
