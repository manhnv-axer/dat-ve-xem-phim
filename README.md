# He thong quan ly ban ve xem phim - C++ OOP

## Kien truc
- `User` la lop co so tru tuong.
- `Staff` ke thua `User`.
- `Roles::Manager` ke thua `Staff`, tach rieng quyen Manager.
- `Customer` ke thua `User`.
- `Ticket` la lop co so tru tuong; `StandardTicket` va `VIPTicket` ke thua `Ticket`.
- `vector<unique_ptr<Ticket>>` trong `Booking` the hien da hinh OOP.
- `Manager<T>` la template dung chung cho cac manager; co `filter(Predicate)`.

## Phan quyen
- Manager: tao/khoa/mo khoa Staff; quan ly phim, showtime, phong/ghe, Customer, thong ke, ban ve tai quay.
- Staff: ban ve tai quay, tra cuu, xem Booking; khong co API quan ly Staff.
- Customer: tra cuu, dat nhieu ghe/Booking, xem lich su, huy Booking neu con >= 30 phut.

## Du lieu
- `data/users.txt`
- `data/movies.txt`
- `data/showtimes.txt`
- `data/rooms.txt`
- `data/bookings.txt`

`rooms.txt` luu rieng so dong, so cot va trang thai VIP/bao tri cua tung ghe. Trang thai da dat khong luu vao phong vi ghe da dat phu thuoc tung Showtime.

## Gia ve
- Standard = gia co ban.
- VIP = `1.5 * gia co ban`.

## Tai khoan mau
- Manager: `admin / admin123`
- Staff: `staff01 / staff123`
- Customer: `customer01 / customer123`

## Build
Chay `build.bat`, sau do `run.bat`.
Trong VS Code co the chay task `Build Cinema C++` hoac `Run Cinema C++`.
