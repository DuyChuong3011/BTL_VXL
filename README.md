**BTL_VXL — Hệ thống đèn giao thông (Traffic Light) trên STM32F103**

Mô tả:

 - Đây là firmware cho mô phỏng hệ thống đèn giao thông hai hướng trên vi điều khiển STM32F103. Hệ thống hỗ trợ 5 chế độ vận hành, điều chỉnh thời gian đèn đỏ/xanh/vàng, và chế độ điều khiển bằng tay.

Tính năng chính:

 - Mode 1 — Tự động: Chạy tuần tự các pha (RED1+GREEN2, RED1+YELLOW2, GREEN1+RED2, YELLOW1+RED2) theo thời gian cấu hình.
 - Mode 2 — Cấu hình thời gian RED: Cho phép tăng giá trị thời gian đèn đỏ và lưu lại.
 - Mode 3 — Cấu hình thời gian GREEN: Cho phép tăng giá trị thời gian đèn xanh và lưu lại.
 - Mode 4 — Cấu hình thời gian YELLOW: Cho phép tăng giá trị thời gian đèn vàng và lưu lại.
 - Mode 5 — Điều khiển bằng tay (Manual): Một chiều xanh, một chiều đỏ; bấm nút để đổi ngược lại.

Các nút và vai trò (theo mã nguồn):

 - `button1`: chuyển giữa các mode (1 → 2 → 3 → 4 → 1)
 - `button2`: trong mode 2/3/4 tăng giá trị thời gian cấu hình (1..99)
 - `button3`: lưu giá trị hiện tại cho mode cấu hình
 - `button4`: vào mode 5 (Manual) và khi ở mode 5 bấm sẽ đổi trạng thái giao thông (đổi chiều xanh/đỏ)

Ghi chú về logic thời gian:

 - Trong code có kiểm tra an toàn: `red_time` phải bằng `green_time + yellow_time`. Nếu không đúng sẽ reset về giá trị mặc định.
 - Giá trị thời gian lưu ở biến `red_time`, `green_time`, `yellow_time`. Các giá trị tạm để chỉnh là `temp` (xem `set.c`).

Các file chính cần xem để hiểu chi tiết:

 - [code/Core/Src/main.c](code/Core/Src/main.c) — Khởi tạo, vòng lặp chính và timer callback
 - [code/Core/Src/button.c](code/Core/Src/button.c) — Đọc và lọc nút bấm, hàm `buttonXpressed()`
 - [code/Core/Src/auto.c](code/Core/Src/auto.c) — Luồng chế độ tự động (`automode()`), cập nhật buffer hiển thị
 - [code/Core/Src/set.c](code/Core/Src/set.c) — Xử lý thay đổi mode, cấu hình thời gian, led blinky, mode 5 manual
 - [code/Core/Src/display.c](code/Core/Src/display.c) — Giao tiếp LCD / hiển thị (xem để biết cách hiển thị thời gian)

Hướng dẫn nhanh sử dụng interface:

 - Khởi động board — hệ thống mặc định về `mode = 1` (tự động).
 - Bấm `button1` để chuyển sang mode 2/3/4 để cấu hình lần lượt RED/GREEN/YELLOW.
 - Trong mode cấu hình, bấm `button2` để tăng `temp` (1..99). Bấm `button3` để lưu `temp` vào biến tương ứng.
 - Bấm `button4` để vào mode 5 (Manual). Ở mode 5, mỗi lần bấm sẽ đổi trạng thái giữa hai chiều (một chiều xanh, chiều còn lại đỏ).

Build & Flash (tóm tắt):

 - Mở project bằng STM32CubeIDE và nhấn Build, hoặc sử dụng toolchain `arm-none-eabi-gcc` với Makefile có sẵn trong thư mục `Debug`.
 - Flash bằng STM32CubeProgrammer hoặc `st-flash`/OpenOCD. Ví dụ dùng `st-flash`:

```powershell
st-flash write Debug/your_firmware.bin 0x8000000
```