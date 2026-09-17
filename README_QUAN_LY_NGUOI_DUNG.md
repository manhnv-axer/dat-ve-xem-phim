# Phan bo sung: Quan ly nguoi dung

## Chuc nang da them

Trong `Menu Quan Ly` co them muc `4. Quan ly Nguoi dung (Customer / Staff)`:

1. Tim kiem khach hang theo ID, username, ho ten, so dien thoai.
2. Xem danh sach nhan vien.
3. Xem danh sach khach hang.
4. Cap / mo khoa tai khoan.
5. Khoa tai khoan.
6. Cap tai khoan nhan vien moi (chi Admin).

## OOP va Template

- `User` la lop cha truu tuong.
- `Customer : public User` va `Staff : public User` the hien ke thua.
- `Manager<T>` la lop khuon mau quan ly du lieu dung lai cho nhieu loai doi tuong.
- Them ham khuon mau `filter(Predicate)` trong `Manager.h` de loc du lieu tai su dung.
- `AccountManager : public Manager<Account>` su dung `filter()` cho tim Customer va lay danh sach Staff.
- Chuc nang quan ly tai khoan duoc tach thanh `.h` va `.cpp`.

## Phan quyen

- Admin: duoc tim/xem Customer, xem Staff, mo khoa/khoa tai khoan va tao tai khoan Staff.
- Staff: duoc tim/xem Customer, xem Staff; khong duoc khoa/mo khoa tai khoan Staff va khong duoc tao Staff.
- Khong cho tu khoa tai khoan dang dang nhap.

## Luu du lieu

Tat ca trang thai Active/Locked va tai khoan moi duoc luu vao `data/users.txt`.

## Kiem tra

Project da duoc build test voi C++17 sau khi dong bo lai phan `CinemaRoom/Seat` dang bi lech header/implementation trong ban goc.
