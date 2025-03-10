#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
// Lớp Giáo viên
class GiaoVien {
public:
    std::string MGV;
    std::string TenGV;
    std::string MonDay;
    std::string SDT;

    GiaoVien(std::string mgv, std::string tengv, std::string monday, std::string sdt)
        : MGV(mgv), TenGV(tengv), MonDay(monday), SDT(sdt) {}

    void inThongTin() const {
        std::cout << "Mã giáo viên: " << MGV << ", Tên giáo viên: " << TenGV
                  << ", Môn dạy: " << MonDay << ", SĐT: " << SDT << std::endl;
    }
};

// Lớp Học sinh
class HocSinh {
public:
    std::string MaHS;
    std::string TenHS;
    std::string Lop;
    std::string DiaChi;
    std::string SDT;
    std::string SDTPH;

    HocSinh(std::string mahs, std::string tenhs, std::string lop, std::string diachi, std::string sdt, std::string sdtph)
        : MaHS(mahs), TenHS(tenhs), Lop(lop), DiaChi(diachi), SDT(sdt), SDTPH(sdtph) {}

    void inThongTin() const {
        std::cout << "Mã học sinh: " << MaHS << ", Tên học sinh: " << TenHS
                  << ", Lớp: " << Lop << ", Địa chỉ: " << DiaChi
                  << ", SĐT: " << SDT << ", SĐT PH: " << SDTPH << std::endl;
    }
};

// Lớp Bảng điểm
class BangDiem {
public:
    std::string MaHS;
    std::string MaMH;
    float DM;
    float DCC;
    float DKT;
    float DT;

    BangDiem(std::string mahs, std::string mamh, float dm, float dcc, float dkt, float dt)
        : MaHS(mahs), MaMH(mamh), DM(dm), DCC(dcc), DKT(dkt), DT(dt) {}

    float diemTrungBinh() const {
        return (DM + DCC + DKT + DT) / 4;
    }

    void inThongTin() const {
        std::cout << "Mã học sinh: " << MaHS << ", Mã môn học: " << MaMH
                  << ", Điểm miệng: " << DM << ", Điểm 15 phút: " << DCC
                  << ", Điểm 45 phút: " << DKT << ", Điểm thi: " << DT
                  << ", Điểm trung bình: " << diemTrungBinh() << std::endl;
    }
};

// Lớp QuanLyTruongHoc
class QuanLyTruongHoc {
private:
    std::vector<GiaoVien> danhSachGV;
    std::vector<HocSinh> danhSachHS;
    std::vector<BangDiem> danhSachBD;

public:
    // Chức năng nhập dữ liệu giáo viên
    void nhapGiaoVien(const GiaoVien& gv) {
        danhSachGV.push_back(gv);
    }

    // Chức năng nhập dữ liệu học sinh
    void nhapHocSinh(const HocSinh& hs) {
        danhSachHS.push_back(hs);
    }

    // Chức năng nhập dữ liệu điểm
    void nhapBangDiem(const BangDiem& bd) {
        danhSachBD.push_back(bd);
    }

    // In danh sách giáo viên
    void inDanhSachGV() const {
        for (const auto& gv : danhSachGV) {
            gv.inThongTin();
        }
    }

    // In danh sách học sinh
    void inDanhSachHS() const {
        for (const auto& hs : danhSachHS) {
            hs.inThongTin();
        }
    }

    // In danh sách điểm theo học sinh
    void inDanhSachDiemTheoHS(const std::string& mahs) const {
        for (const auto& bd : danhSachBD) {
            if (bd.MaHS == mahs) {
                bd.inThongTin();
            }
        }
    }

    // In danh sách điểm theo môn
    void inDanhSachDiemTheoMon(const std::string& mamh) const {
        for (const auto& bd : danhSachBD) {
            if (bd.MaMH == mamh) {
                bd.inThongTin();
            }
        }
    }

    // Báo cáo kết quả học tập theo lớp
    void baoCaoKQTheoLop(const std::string& lop) const {
        for (const auto& hs : danhSachHS) {
            if (hs.Lop == lop) {
                std::cout << "Học sinh: " << hs.TenHS << std::endl;
                inDanhSachDiemTheoHS(hs.MaHS);
            }
        }
    }

    // In danh sách điểm trung bình của học sinh
    void inDanhSachDiemTB() const {
        for (const auto& bd : danhSachBD) {
            std::cout << "Mã học sinh: " << bd.MaHS << ", Điểm trung bình: " << bd.diemTrungBinh() << std::endl;
        }
    }

    // Hiển thị học sinh có điểm trung bình cao nhất
    void hienThiHSCaoNhat() const {
        if (danhSachBD.empty()) return;

        auto maxElem = std::max_element(danhSachBD.begin(), danhSachBD.end(),
                                        [](const BangDiem& a, const BangDiem& b) {
                                            return a.diemTrungBinh() < b.diemTrungBinh();
                                        });

        std::cout << "Học sinh có điểm trung bình cao nhất: " << maxElem->MaHS << ", Điểm trung bình: " << maxElem->diemTrungBinh() << std::endl;
    }

    // Xếp loại học lực
    std::string xepLoaiHocLuc(const std::string& mahs) const {
        float diemTB = 0;
        int count = 0;
        for (const auto& bd : danhSachBD) {
            if (bd.MaHS == mahs) {
                diemTB += bd.diemTrungBinh();
                count++;
            }
        }
        if (count == 0) return "Không có điểm";

        diemTB /= count;
        if (diemTB >= 8.0) return "Giỏi";
        if (diemTB >= 6.5) return "Khá";
        if (diemTB >= 5.0) return "Trung bình";
        return "Yếu";
    }

    // Tìm kiếm giáo viên theo tên
    void timKiemGV(const std::string& tenGV) const {
        for (const auto& gv : danhSachGV) {
            if (gv.TenGV == tenGV) {
                gv.inThongTin();
            }
        }
    }

    // Tìm kiếm học sinh theo tên
    void timKiemHS(const std::string& tenHS) const {
        for (const auto& hs : danhSachHS) {
            if (hs.TenHS == tenHS) {
                hs.inThongTin();
            }
        }
    }
};
