CÁC BƯỚC THỰC HIỆN:
1. Cấu hình GPIO:
  - PA5: Output push-pull (kết nối LED).
  - PA9 (TX): Alternate Function Push-pull.
  - PA10 (RX): Input Floating.
    
<img width="958" height="383" alt="image" src="https://github.com/user-attachments/assets/aa34638e-3f74-432c-8d84-d63ddf6c1d4e" />

2. Cấu hình USART:
   - Baudrate: 115200
   - Data: 8 bit
   - Stop bit: 1
   - Parity: None
   - Mode: Rx | Tx
   - Bật ngắt RXNE để nhận dữ liệu.
   - 
<img width="780" height="493" alt="image" src="https://github.com/user-attachments/assets/ece6d474-a66f-40db-82f0-0a759de32be7" />

3. Hàm gửi USART:
   - Print_Char: gửi 1 ký tự.
   - Print_String: gửi cả chuỗi.
   - 
     <img width="743" height="278" alt="image" src="https://github.com/user-attachments/assets/447cd081-62ec-4d1f-9ded-c249dad60828" />

4. Trình phục vụ ngắt USART:
   - Nhận dữ liệu từ máy tính.
   - Nếu gặp \n → kết thúc chuỗi lệnh.
   - Lưu dữ liệu vào command[].
   - Echo (in lại ký tự vừa nhập).
  
     <img width="627" height="474" alt="image" src="https://github.com/user-attachments/assets/0a53a56f-3310-417f-8f8a-1a0f3e24fe01" />

5. Chương trình chính:
  - Khởi tạo GPIO, UART.
  - Gửi chuỗi chào "Hello FROM STM32 !".
  - Nếu nhận lệnh "ON" → bật LED PA5.
  - Nếu nhận lệnh "OFF" → tắt LED PA5.
  - Nếu sai lệnh → in "Invalid command".
    
    <img width="963" height="651" alt="image" src="https://github.com/user-attachments/assets/86f5dc86-56bd-47da-89b1-c6df21eafd50" />

6. Kết quả:
  - STM32 gửi chuỗi "Hello FROM STM32 !" khi khởi động.
  - "ON" → LED PA5 sáng.
  - "OFF" → LED PA5 tắt.
  - Lệnh khác → báo "Invalid command".

