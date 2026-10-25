#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_CAU_THU 100

/* ===== STRUCT: giu nguyen 7 truong da thong nhat ===== */
typedef struct
{
    char maCT[10];
    char hoTen[50];
    char viTri[20];
    int soAo;
    int tuoi;
    int soBanThang;
    float luongTuan;
} CauThu;

/* ===== BIEN TOAN CUC ===== */
CauThu doiBong[MAX_CAU_THU];
int soLuong = 0;

void taiDuLieu(void);
void luuDuLieu(void);

/* ===== FUNCTION PROTOTYPES ===== */
void boKyTuThua(void);
int nhapDong(const char thongBao[], char noiDung[], int kichThuoc);
void xoaKhoangTrang(char chuoi[]);
int chuoiRong(char chuoi[]);
int laBlank(char chuoi[]);
int tenHopLe(char ten[]);
int maHopLe(char ma[]);
int kiemTraMaTrung(char maCanKiem[]);
int nhapMa(const char thongBao[], char ma[]);
int nhapTen(const char thongBao[], char ten[], int kichThuoc);
int nhapChuoiBatBuoc(const char thongBao[], char chuoi[], int kichThuoc);
int nhapSo(const char thongBao[], int min, int max, int *so);
int nhapSoKhongAm(const char thongBao[], int *so);
int nhapLuong(const char thongBao[], float *luong);
int timViTriMa(char ma[]);
void inThongTinCauThu(CauThu ct);
void themCauThu(void);
void timKiemCauThu(void);
void capNhatCauThu(void);
void xoaCauThu(void);
void hienThiDanhSach(void);
void thongKe(void);
void sapXep(void);
void locCauThu(void);

/* ===== MAIN - MENU ===== */
int main(void)
{
    int luaChon;

    taiDuLieu();

    do
    {
        printf("\n===== QUAN LY CAU THU =====\n");
        printf("1. Them cau thu moi\n");
        printf("2. Hien thi danh sach cau thu\n");
        printf("3. Tim kiem cau thu (theo ma / ten)\n");
        printf("4. Cap nhat thong tin cau thu (theo ma)\n");
        printf("5. Xoa cau thu (theo ma)\n");
        printf("6. Thong ke (chua trien khai)\n");
        printf("7. Sap xep (chua trien khai)\n");
        printf("8. Loc cau thu (chua trien khai)\n");
        printf("0. Thoat\n");

        if (!nhapSo("Nhap lua chon: ", 0, 8, &luaChon))
        {
            break;
        }

        switch (luaChon)
        {
            case 1: themCauThu(); break;
            case 2: hienThiDanhSach(); break;
            case 3: timKiemCauThu(); break;
            case 4: capNhatCauThu(); break;
            case 5: xoaCauThu(); break;
            case 6: thongKe(); break;
            case 7: sapXep(); break;
            case 8: locCauThu(); break;
            case 0: printf("Chao tam biet!\n"); break;
        }
    }
    while (luaChon != 0);

    return 0;
}

/* ===== LUU VA DOC DU LIEU CAU THU ===== */
void taiDuLieu(void)
{
    FILE *f = fopen("cauthu.txt", "r");
    char dong[256];
    CauThu ct;

    if (f == NULL)
        return;

    while (soLuong < MAX_CAU_THU && fgets(dong, sizeof(dong), f) != NULL)
    {
        if (sscanf(dong, "%9[^|]|%49[^|]|%19[^|]|%d|%d|%d|%f",
                   ct.maCT, ct.hoTen, ct.viTri,
                   &ct.soAo, &ct.tuoi, &ct.soBanThang,
                   &ct.luongTuan) == 7)
        {
            doiBong[soLuong] = ct;
            soLuong++;
        }
    }

    fclose(f);
}

void luuDuLieu(void)
{
    FILE *f = fopen("cauthu.txt", "w");
    int i;

    if (f == NULL)
    {
        printf("Loi: khong the luu du lieu vao file!\n");
        return;
    }

    for (i = 0; i < soLuong; i++)
    {
        fprintf(f, "%s|%s|%s|%d|%d|%d|%.2f\n",
                doiBong[i].maCT,
                doiBong[i].hoTen,
                doiBong[i].viTri,
                doiBong[i].soAo,
                doiBong[i].tuoi,
                doiBong[i].soBanThang,
                doiBong[i].luongTuan);
    }

    fclose(f);
}

/* ===== CAC HAM NHAP DU LIEU CO BAN ===== */

void boKyTuThua(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {

    }
}

int nhapDong(const char thongBao[], char noiDung[], int kichThuoc)
{
    int i;

    printf("%s", thongBao);
    if (fgets(noiDung, kichThuoc, stdin) == NULL)
    {
        return 0;
    }

    for (i = 0; noiDung[i] != '\0'; i++)
    {
        if (noiDung[i] == '\n')
        {
            noiDung[i] = '\0';
            return 1;
        }
    }

    if (!feof(stdin))
    {
        boKyTuThua();
        printf("Du lieu qua dai, vui long nhap lai.\n");
        return -1;
    }

    return 1;
}

void xoaKhoangTrang(char chuoi[])
{
    int dau = 0;
    int cuoi = 0;

    while (chuoi[dau] == ' ' || chuoi[dau] == '\t')
    {
        dau++;
    }

    while (chuoi[dau] != '\0')
    {
        chuoi[cuoi] = chuoi[dau];
        cuoi++;
        dau++;
    }
    chuoi[cuoi] = '\0';

    while (cuoi > 0 && (chuoi[cuoi - 1] == ' ' || chuoi[cuoi - 1] == '\t'))
    {
        cuoi--;
        chuoi[cuoi] = '\0';
    }
}

int chuoiRong(char chuoi[])
{
    int i;
    for (i = 0; chuoi[i] != '\0'; i++)
    {
        if (chuoi[i] != ' ' && chuoi[i] != '\t')
        {
            return 0;
        }
    }
    return 1;
}

int laBlank(char chuoi[])
{
    int i;
    char tuBlank[] = "blank";

    if (strlen(chuoi) != 5)
    {
        return 0;
    }

    for (i = 0; i < 5; i++)
    {
        if (tolower((unsigned char)chuoi[i]) != tuBlank[i])
        {
            return 0;
        }
    }
    return 1;
}

int tenHopLe(char ten[])
{
    int i;
    int coChu = 0;

    for (i = 0; ten[i] != '\0'; i++)
    {
        char c = ten[i];

        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        {
            coChu = 1;
        }
        else if (c == ' ' || c == '-' || c == '\'' || c == '.')
        {
        }
        else
        {
            return 0;
        }
    }

    return coChu;
}

int maHopLe(char ma[])
{
    int i;
    int doDai = (int)strlen(ma);

    if (doDai < 2 || doDai > 9)
    {
        return 0;
    }

    for (i = 0; ma[i] != '\0'; i++)
    {
        if (!((ma[i] >= 'A' && ma[i] <= 'Z') ||
              (ma[i] >= 'a' && ma[i] <= 'z') ||
              (ma[i] >= '0' && ma[i] <= '9')))
        {
            return 0;
        }
    }
    return 1;
}

int nhapMa(const char thongBao[], char ma[])
{
    char dong[100];
    int ketQua;

    while (1)
    {
        ketQua = nhapDong(thongBao, dong, 100);
        if (ketQua == 0)
        {
            return 0;
        }
        if (ketQua == -1)
        {
            continue;
        }

        if (!maHopLe(dong))
        {
            printf("Ma chi gom 2-9 ky tu chu cai va chu so, khong co khoang trang hay ky tu dac biet.\n");
            continue;
        }

        strcpy(ma, dong);
        return 1;
    }
}

int nhapTen(const char thongBao[], char ten[], int kichThuoc)
{
    int ketQua;

    while (1)
    {
        ketQua = nhapDong(thongBao, ten, kichThuoc);
        if (ketQua == 0)
        {
            return 0;
        }
        if (ketQua == -1)
        {
            continue;
        }

        xoaKhoangTrang(ten);

        if (chuoiRong(ten) || laBlank(ten))
        {
            printf("Khong duoc de trong hoac nhap tu blank. Vui long nhap lai.\n");
            continue;
        }

        if (!tenHopLe(ten))
        {
            printf("Ten/vi tri chi dung chu cai khong dau, khoang trang, dau -, dau nhay hoac dau cham.\n");
            continue;
        }

        return 1;
    }
}

int nhapChuoiBatBuoc(const char thongBao[], char chuoi[], int kichThuoc)
{
    int ketQua;

    while (1)
    {
        ketQua = nhapDong(thongBao, chuoi, kichThuoc);
        if (ketQua == 0)
        {
            return 0;
        }
        if (ketQua == -1)
        {
            continue;
        }

        xoaKhoangTrang(chuoi);
        if (chuoiRong(chuoi) || laBlank(chuoi))
        {
            printf("Khong duoc de trong hoac nhap tu blank. Vui long nhap lai.\n");
            continue;
        }
        return 1;
    }
}

int nhapSo(const char thongBao[], int min, int max, int *so)
{
    char dong[100];
    char kyTuThem;
    int giaTri;
    int ketQua;

    while (1)
    {
        ketQua = nhapDong(thongBao, dong, 100);
        if (ketQua == 0)
        {
            return 0;
        }
        if (ketQua == -1)
        {
            continue;
        }

        if (sscanf(dong, "%d %c", &giaTri, &kyTuThem) != 1)
        {
            printf("Vui long nhap mot so nguyen.\n");
            continue;
        }

        if (giaTri < min || giaTri > max)
        {
            printf("Gia tri phai tu %d den %d. Vui long nhap lai.\n", min, max);
            continue;
        }

        *so = giaTri;
        return 1;
    }
}

int nhapSoKhongAm(const char thongBao[], int *so)
{
    char dong[100];
    char kyTuThem;
    int giaTri;
    int ketQua;

    while (1)
    {
        ketQua = nhapDong(thongBao, dong, 100);
        if (ketQua == 0)
        {
            return 0;
        }
        if (ketQua == -1)
        {
            continue;
        }

        if (sscanf(dong, "%d %c", &giaTri, &kyTuThem) != 1)
        {
            printf("Vui long nhap mot so nguyen.\n");
            continue;
        }

        if (giaTri < 0 || giaTri > 980)
        {
            printf("So ban thang phai tu 0 den 980. Vui long nhap lai.\n");
            continue;
        }

        *so = giaTri;
        return 1;
    }
}

int nhapLuong(const char thongBao[], float *luong)
{
    char dong[100];
    char kyTuThem;
    float giaTri;
    int ketQua;

    while (1)
    {
        ketQua = nhapDong(thongBao, dong, 100);
        if (ketQua == 0)
        {
            return 0;
        }
        if (ketQua == -1)
        {
            continue;
        }

        if (sscanf(dong, "%f %c", &giaTri, &kyTuThem) != 1)
        {
            printf("Vui long nhap mot so.\n");
            continue;
        }

        if (!(giaTri >= 0))
        {
            printf("Luong tuan phai lon hon hoac bang 0. Vui long nhap lai.\n");
            continue;
        }

        *luong = giaTri;
        return 1;
    }
}

/* ===== QUAN: THEM CAU THU ===== */
int kiemTraMaTrung(char maCanKiem[])
{
    int i;
    for (i = 0; i < soLuong; i++)
    {
        if (strcmp(doiBong[i].maCT, maCanKiem) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void themCauThu(void)
{
    CauThu moi;

    if (soLuong >= MAX_CAU_THU)
    {
        printf("Danh sach da day.\n");
        return;
    }

    while (1)
    {
        if (!nhapMa("Nhap ma cau thu (VD: CT001): ", moi.maCT))
        {
            return;
        }
        if (kiemTraMaTrung(moi.maCT))
        {
            printf("Ma da ton tai! Moi nhap lai.\n");
        }
        else
        {
            break;
        }
    }

    if (!nhapTen("Nhap ho ten: ", moi.hoTen, 50)) return;
    if (!nhapTen("Nhap vi tri: ", moi.viTri, 20)) return;
    if (!nhapSo("Nhap so ao (1-99): ", 1, 99, &moi.soAo)) return;
    if (!nhapSo("Nhap tuoi (16-45): ", 16, 45, &moi.tuoi)) return;
    if (!nhapSoKhongAm("Nhap so ban thang (0-980): ", &moi.soBanThang)) return;
    if (!nhapLuong("Nhap luong tuan (trieu dong, >= 0): ", &moi.luongTuan)) return;

    doiBong[soLuong] = moi;
    soLuong++;
    luuDuLieu();
    printf("Them cau thu thanh cong!\n");
}

/* ===== LONG: TIM KIEM CAU THU ===== */
void timKiemCauThu(void)
{
    int kieu, i, thay = 0;
    char key[100];
    char chuoi[100];
    int j;

    if (soLuong == 0)
    {
        printf("Danh sach dang trong!\n");
        return;
    }

    if (!nhapSo("1. Tim theo ma\n2. Tim theo ten\nChon: ", 1, 2, &kieu)) return;

    if (kieu == 1)
    {
        if (!nhapMa("Nhap ma can tim: ", key)) return;
    }
    else
    {
        if (!nhapChuoiBatBuoc("Nhap ten hoac mot phan ten can tim: ", key, 100)) return;
    }

    for (i = 0; i < soLuong; i++)
    {
        if (kieu == 1)
        {
            if (strcmp(doiBong[i].maCT, key) == 0)
            {
                inThongTinCauThu(doiBong[i]);
                thay = 1;
            }
        }
        else
        {
            strcpy(chuoi, doiBong[i].hoTen);
            for (j = 0; chuoi[j] != '\0'; j++)
            {
                chuoi[j] = (char)tolower((unsigned char)chuoi[j]);
            }
            for (j = 0; key[j] != '\0'; j++)
            {
                key[j] = (char)tolower((unsigned char)key[j]);
            }

            if (strstr(chuoi, key) != NULL)
            {
                inThongTinCauThu(doiBong[i]);
                thay = 1;
            }
        }
    }

    if (!thay)
    {
        printf("Khong tim thay cau thu nao!\n");
    }
}

/* ===== CAC HAM DUNG CHUNG CHO CAP NHAT / XOA ===== */
int timViTriMa(char ma[])
{
    int i;
    for (i = 0; i < soLuong; i++)
    {
        if (strcmp(doiBong[i].maCT, ma) == 0)
        {
            return i;
        }
    }
    return -1;
}

void inThongTinCauThu(CauThu ct)
{
    printf("Ma cau thu: %s\n", ct.maCT);
    printf("Ho ten: %s\n", ct.hoTen);
    printf("Vi tri: %s\n", ct.viTri);
    printf("So ao: %d\n", ct.soAo);
    printf("Tuoi: %d\n", ct.tuoi);
    printf("So ban thang: %d\n", ct.soBanThang);
    printf("Luong tuan: %.1f trieu dong\n", ct.luongTuan);
}

/* ===== CAP NHAT CAU THU ===== */
void capNhatCauThu(void)
{
    int vt, soAo, tuoi, soBanThang;
    float luong;
    char ma[10], hoTen[50], viTri[20];

    if (soLuong == 0)
    {
        printf("Danh sach dang trong!\n");
        return;
    }

    if (!nhapMa("Nhap ma cau thu can cap nhat: ", ma)) return;
    vt = timViTriMa(ma);

    if (vt == -1)
    {
        printf("Khong tim thay cau thu co ma %s!\n", ma);
        return;
    }

    printf("Thong tin hien tai:\n");
    inThongTinCauThu(doiBong[vt]);
    printf("Nhap thong tin moi (ma cau thu khong doi):\n");

    if (!nhapTen("Nhap ho ten: ", hoTen, 50)) return;
    if (!nhapTen("Nhap vi tri: ", viTri, 20)) return;
    if (!nhapSo("Nhap so ao (1-99): ", 1, 99, &soAo)) return;
    if (!nhapSo("Nhap tuoi (16-45): ", 16, 45, &tuoi)) return;
    if (!nhapSoKhongAm("Nhap so ban thang (0-980): ", &soBanThang)) return;
    if (!nhapLuong("Nhap luong tuan (trieu dong, >= 0): ", &luong)) return;

    strcpy(doiBong[vt].hoTen, hoTen);
    strcpy(doiBong[vt].viTri, viTri);
    doiBong[vt].soAo = soAo;
    doiBong[vt].tuoi = tuoi;
    doiBong[vt].soBanThang = soBanThang;
    doiBong[vt].luongTuan = luong;

    luuDuLieu();
    printf("Cap nhat cau thu thanh cong!\n");
}

/* ===== XOA CAU THU ===== */
void xoaCauThu(void)
{
    char ma[10];
    int vt, i;

    if (soLuong == 0)
    {
        printf("Danh sach dang trong!\n");
        return;
    }

    if (!nhapMa("Nhap ma cau thu can xoa: ", ma)) return;
    vt = timViTriMa(ma);

    if (vt == -1)
    {
        printf("Khong tim thay cau thu co ma %s!\n", ma);
        return;
    }

    printf("Thong tin cau thu se bi xoa:\n");
    inThongTinCauThu(doiBong[vt]);

    for (i = vt; i < soLuong - 1; i++)
    {
        doiBong[i] = doiBong[i + 1];
    }
    soLuong--;
    luuDuLieu();
    printf("Xoa cau thu thanh cong!\n");
}

/* ===== MINH: HIEN THI DANH SACH ===== */
void hienThiDanhSach(void)
{
    int i;

    if (soLuong == 0)
    {
        printf("Danh sach trong!\n");
        return;
    }

    printf("%-8s %-20s %-18s %-8s %-6s %-12s %-12s\n",
           "Ma", "Ho ten", "Vi tri", "So ao", "Tuoi", "Ban thang", "Luong/tuan");
    printf("--------------------------------------------------------------------------------\n");

    for (i = 0; i < soLuong; i++)
    {
        printf("%-8s %-20s %-18s %-8d %-6d %-12d %-12.1f\n",
               doiBong[i].maCT, doiBong[i].hoTen, doiBong[i].viTri,
               doiBong[i].soAo, doiBong[i].tuoi,
               doiBong[i].soBanThang, doiBong[i].luongTuan);
    }
}

/* ===== CAC HAM NAY DE NGUYEN CHUA TRIEN KHAI ===== */
void thongKe(void)
{
        if (soLuong == 0)
    {
        printf("Danh sach trong!\n");
        return;
    }

    int tongBanThang = 0;
    float tongLuong = 0;
    int maxBanThang = doiBong[0].soBanThang;

    for (int i = 0; i < soLuong; i++)
    {
        tongBanThang += doiBong[i].soBanThang;
        tongLuong += doiBong[i].luongTuan;
        if (doiBong[i].soBanThang > maxBanThang)
        {
            maxBanThang = doiBong[i].soBanThang;
        }
    }

    printf("Tong so ban thang: %d\n", tongBanThang);
    printf("Tong quy luong/tuan: %.1f trieu dong\n", tongLuong);
    printf("Luong trung binh: %.1f trieu dong/tuan\n", tongLuong / soLuong);

    if (maxBanThang == 0)
    {
        printf("Vua pha luoi: chua co ai ghi ban\n");
        return;
    }
    printf("Vua pha luoi (%d ban thang):\n", maxBanThang);
    for (int i = 0; i < soLuong; i++)
    {
        if (doiBong[i].soBanThang == maxBanThang)
        {
            printf("  - %s (%s)\n", doiBong[i].hoTen, doiBong[i].maCT);
        }
    }
}

void sapXep(void)
{
        if (soLuong == 0)
    {
        printf("Danh sach trong!\n");
        return;
    }

    // Giam dan theo so ban thang; bang nhau thi theo ma tang dan
    for (int i = 0; i < soLuong - 1; i++)
    {
        for (int j = i + 1; j < soLuong; j++)
        {
            int doiCho = 0;
            if (doiBong[j].soBanThang > doiBong[i].soBanThang)
            {
                doiCho = 1;
            }
            else if (doiBong[j].soBanThang == doiBong[i].soBanThang
                     && strcmp(doiBong[j].maCT, doiBong[i].maCT) < 0)
            {
                doiCho = 1;
            }

            if (doiCho == 1)
            {
                CauThu tam = doiBong[i];
                doiBong[i] = doiBong[j];
                doiBong[j] = tam;
            }
        }
    }

    printf("Da sap xep theo so ban thang giam dan (bang nhau thi theo ma).\n");
    hienThiDanhSach();
}

void locCauThu(void)
{
        if (soLuong == 0)
    {
        printf("Danh sach trong!\n");
        return;
    }

    int chon = 0;
    printf("Chon vi tri can loc:\n");
    printf("1. Tien dao\n2. Tien ve\n3. Hau ve\n4. Thu mon\n");
    printf("Nhap lua chon (1-4): ");
    if (scanf("%d", &chon) != 1 || chon < 1 || chon > 4)
    {
        printf("Lua chon khong hop le!\n");
        int kyTu;
        while ((kyTu = getchar()) != '\n' && kyTu != EOF)
        {
        }
        return;
    }

    const char *viTriLoc = "Tien dao";
    if (chon == 2)
    {
        viTriLoc = "Tien ve";
    }
    else if (chon == 3)
    {
        viTriLoc = "Hau ve";
    }
    else if (chon == 4)
    {
        viTriLoc = "Thu mon";
    }

    int soKetQua = 0;
    for (int i = 0; i < soLuong; i++)
    {
        if (strcmp(doiBong[i].viTri, viTriLoc) == 0)
        {
            if (soKetQua == 0)
            {
                printf("%-8s%-20s%-10s%-8s%-6s%-11s%-8s\n", "Ma", "Ho ten", "Vi tri", "So ao", "Tuoi", "Ban thang", "Luong");
                printf("-----------------------------------------------------------------------\n");
            }
            printf("%-8s%-20s%-10s%-8d%-6d%-11d%-8.1f\n",
                   doiBong[i].maCT, doiBong[i].hoTen, doiBong[i].viTri,
                   doiBong[i].soAo, doiBong[i].tuoi, doiBong[i].soBanThang, doiBong[i].luongTuan);
            soKetQua++;
        }
    }

    if (soKetQua == 0)
    {
        printf("Khong co cau thu nao o vi tri %s!\n", viTriLoc);
    }
}
