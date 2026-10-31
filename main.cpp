#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_CAU_THU 100
#define LUONG_TUAN_TOI_DA 1000

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
int viTriHopLe(char viTri[]);
const char *tenViTri(int chon);
int kiemTraMaTrung(char maCanKiem[]);
int kiemTraSoAoTrung(int soAoCanKiem, int boQua);
int nhapMa(const char thongBao[], char ma[]);
int nhapTen(const char thongBao[], char ten[], int kichThuoc);
int nhapViTri(char viTri[]);
int nhapSo(const char thongBao[], int min, int max, int *so);
int nhapSoKhongAm(const char thongBao[], int *so);
int nhapLuong(const char thongBao[], float *luong);
int nhapTenGiuNguyen(const char thongBao[], char tenMoi[], int kichThuoc);
int nhapSoGiuNguyen(const char thongBao[], int min, int max, int *so);
int nhapLuongGiuNguyen(const char thongBao[], float *luong);
int timViTriMa(char ma[]);
void inTieuDeBang(void);
void inHangCauThu(CauThu ct);
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
        printf("6. Thong ke\n");
        printf("7. Sap xep\n");
        printf("8. Loc cau thu\n");
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
                   &ct.luongTuan) == 7 && viTriHopLe(ct.viTri))
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

    while (isspace((unsigned char)chuoi[dau]))
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

    while (cuoi > 0 && isspace((unsigned char)chuoi[cuoi - 1]))
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
        if (!isspace((unsigned char)chuoi[i]))
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

/* Ten chi gom chu cai (ctype: isalpha), khoang trang, -, ' hoac . */
int tenHopLe(char ten[])
{
    int i;
    int coChu = 0;

    for (i = 0; ten[i] != '\0'; i++)
    {
        unsigned char c = (unsigned char)ten[i];

        if (isalpha(c))
        {
            coChu = 1;
        }
        else if (isspace(c) || c == '-' || c == '\'' || c == '.')
        {
        }
        else
        {
            return 0;
        }
    }

    return coChu;
}

/* Ma chi gom 2-9 ky tu chu cai hoac chu so (ctype: isalnum) */
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
        if (!isalnum((unsigned char)ma[i]))
        {
            return 0;
        }
    }
    return 1;
}

/* Vi tri chi duoc 1 trong 4 gia tri chuan */
int viTriHopLe(char viTri[])
{
    return strcmp(viTri, "Tien dao") == 0 ||
           strcmp(viTri, "Tien ve") == 0 ||
           strcmp(viTri, "Hau ve") == 0 ||
           strcmp(viTri, "Thu mon") == 0;
}

const char *tenViTri(int chon)
{
    if (chon == 1)
    {
        return "Tien dao";
    }
    if (chon == 2)
    {
        return "Tien ve";
    }
    if (chon == 3)
    {
        return "Hau ve";
    }
    return "Thu mon";
}

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

/* boQua = vi tri cua cau thu dang cap nhat (khong tinh chinh minh);
   truyen -1 khi them moi */
int kiemTraSoAoTrung(int soAoCanKiem, int boQua)
{
    int i;
    for (i = 0; i < soLuong; i++)
    {
        if (i != boQua && doiBong[i].soAo == soAoCanKiem)
        {
            return 1;
        }
    }
    return 0;
}

/* Tra 1: nhap duoc ma hop le; 0: huy (nhap 0 hoac Ctrl+Z) */
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

        if (strcmp(dong, "0") == 0)
        {
            return 0;
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

/* Tra 1: nhap duoc ten hop le; 0: huy (nhap 0 hoac Ctrl+Z) */
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

        if (strcmp(ten, "0") == 0)
        {
            return 0;
        }

        if (chuoiRong(ten) || laBlank(ten))
        {
            printf("Khong duoc de trong hoac nhap tu blank. Vui long nhap lai.\n");
            continue;
        }

        if (!tenHopLe(ten))
        {
            printf("Ten chi dung chu cai khong dau, khoang trang, dau -, dau nhay hoac dau cham.\n");
            continue;
        }

        return 1;
    }
}

/* Chon vi tri bang menu 1-4. Tra 1: chon duoc vi tri moi;
   0: chon 0 (giu nguyen); -1: huy (Ctrl+Z) */
int nhapViTri(char viTri[])
{
    int chon;

    printf("Chon vi tri:\n");
    printf("1. Tien dao\n2. Tien ve\n3. Hau ve\n4. Thu mon\n0. Khong thay doi\n");
    if (!nhapSo("Nhap lua chon (0-4): ", 0, 4, &chon))
    {
        return -1;
    }
    if (chon == 0)
    {
        return 0;
    }

    strcpy(viTri, tenViTri(chon));
    return 1;
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

        if (chuoiRong(dong))
        {
            printf("Khong duoc de trong. Vui long nhap lai.\n");
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

        if (chuoiRong(dong))
        {
            printf("Khong duoc de trong. Vui long nhap lai.\n");
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

/* Luong tuan gioi han 0-1000 trieu dong.
   NaN bi loai vi moi phep so sanh voi NaN deu sai (giaTri >= 0 sai);
   +inf bi loai vi vuot qua muc tran 1000. */
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

        if (chuoiRong(dong))
        {
            printf("Khong duoc de trong. Vui long nhap lai.\n");
            continue;
        }

        if (sscanf(dong, "%f %c", &giaTri, &kyTuThem) != 1)
        {
            printf("Vui long nhap mot so.\n");
            continue;
        }

        if (!(giaTri >= 0))
        {
            printf("Luong khong duoc la NaN hay so am. Vui long nhap lai.\n");
            continue;
        }

        if (giaTri > LUONG_TUAN_TOI_DA)
        {
            printf("Luong tuan toi da %d trieu dong. Vui long nhap lai.\n", LUONG_TUAN_TOI_DA);
            continue;
        }

        *luong = giaTri;
        return 1;
    }
}

/* ===== CAC HAM PHUC VU CAP NHAT: Enter = giu nguyen =====
   Tra 1: co gia tri moi hop le; 0: Enter giu nguyen; -1: huy (Ctrl+Z) */

int nhapTenGiuNguyen(const char thongBao[], char tenMoi[], int kichThuoc)
{
    int ketQua;

    while (1)
    {
        ketQua = nhapDong(thongBao, tenMoi, kichThuoc);
        if (ketQua == 0)
        {
            return -1;
        }
        if (ketQua == -1)
        {
            continue;
        }

        xoaKhoangTrang(tenMoi);

        if (chuoiRong(tenMoi))
        {
            return 0;
        }

        if (laBlank(tenMoi) || !tenHopLe(tenMoi))
        {
            printf("Ten chi dung chu cai khong dau, khoang trang, dau -, dau nhay hoac dau cham.\n");
            continue;
        }

        return 1;
    }
}

int nhapSoGiuNguyen(const char thongBao[], int min, int max, int *so)
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
            return -1;
        }
        if (ketQua == -1)
        {
            continue;
        }

        xoaKhoangTrang(dong);

        if (chuoiRong(dong))
        {
            return 0;
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

int nhapLuongGiuNguyen(const char thongBao[], float *luong)
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
            return -1;
        }
        if (ketQua == -1)
        {
            continue;
        }

        xoaKhoangTrang(dong);

        if (chuoiRong(dong))
        {
            return 0;
        }

        if (sscanf(dong, "%f %c", &giaTri, &kyTuThem) != 1)
        {
            printf("Vui long nhap mot so.\n");
            continue;
        }

        if (!(giaTri >= 0))
        {
            printf("Luong khong duoc la NaN hay so am. Vui long nhap lai.\n");
            continue;
        }

        if (giaTri > LUONG_TUAN_TOI_DA)
        {
            printf("Luong tuan toi da %d trieu dong. Vui long nhap lai.\n", LUONG_TUAN_TOI_DA);
            continue;
        }

        *luong = giaTri;
        return 1;
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

/* Mot dinh dang bang duy nhat cho moi cho hien thi */
void inTieuDeBang(void)
{
    printf("%-8s %-20s %-18s %-8s %-6s %-12s %-12s\n",
           "Ma", "Ho ten", "Vi tri", "So ao", "Tuoi", "Ban thang", "Luong/tuan");
    printf("--------------------------------------------------------------------------------\n");
}

void inHangCauThu(CauThu ct)
{
    printf("%-8s %-20s %-18s %-8d %-6d %-12d %-12.1f\n",
           ct.maCT, ct.hoTen, ct.viTri,
           ct.soAo, ct.tuoi, ct.soBanThang, ct.luongTuan);
}

/* ===== QUAN: THEM CAU THU ===== */
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
        if (!nhapMa("Nhap ma cau thu (VD: CT001, 0 de huy): ", moi.maCT))
        {
            printf("Da huy them cau thu.\n");
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

    if (!nhapTen("Nhap ho ten (0 de huy): ", moi.hoTen, 50))
    {
        printf("Da huy them cau thu.\n");
        return;
    }

    if (nhapViTri(moi.viTri) <= 0)
    {
        printf("Da huy them cau thu.\n");
        return;
    }

    while (1)
    {
        if (!nhapSo("Nhap so ao (1-99): ", 1, 99, &moi.soAo))
        {
            printf("Da huy them cau thu.\n");
            return;
        }
        if (kiemTraSoAoTrung(moi.soAo, -1))
        {
            printf("So ao %d da co nguoi dung! Moi nhap lai.\n", moi.soAo);
        }
        else
        {
            break;
        }
    }

    if (!nhapSo("Nhap tuoi (16-45): ", 16, 45, &moi.tuoi))
    {
        printf("Da huy them cau thu.\n");
        return;
    }
    if (!nhapSoKhongAm("Nhap so ban thang (0-980): ", &moi.soBanThang))
    {
        printf("Da huy them cau thu.\n");
        return;
    }
    if (!nhapLuong("Nhap luong tuan (trieu dong, 0-1000): ", &moi.luongTuan))
    {
        printf("Da huy them cau thu.\n");
        return;
    }

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
    int ketQua;

    if (soLuong == 0)
    {
        printf("Danh sach dang trong!\n");
        return;
    }

    printf("1. Tim theo ma\n2. Tim theo ten\n0. Quay lai menu\n");
    if (!nhapSo("Chon: ", 0, 2, &kieu))
    {
        return;
    }
    if (kieu == 0)
    {
        return;
    }

    if (kieu == 1)
    {
        if (!nhapMa("Nhap ma can tim (0 de huy): ", key))
        {
            return;
        }
    }
    else
    {
        while (1)
        {
            ketQua = nhapDong("Nhap ten hoac mot phan ten can tim (0 de huy): ", key, 100);
            if (ketQua == 0)
            {
                return;
            }
            if (ketQua == -1)
            {
                continue;
            }
            xoaKhoangTrang(key);
            if (strcmp(key, "0") == 0)
            {
                return;
            }
            if (chuoiRong(key))
            {
                printf("Tu khoa khong duoc de trong. Vui long nhap lai.\n");
                continue;
            }
            break;
        }

        /* Ha chu thuong tu khoa 1 lan truoc khi so sanh */
        for (j = 0; key[j] != '\0'; j++)
        {
            key[j] = (char)tolower((unsigned char)key[j]);
        }
    }

    for (i = 0; i < soLuong; i++)
    {
        int khop = 0;

        if (kieu == 1)
        {
            if (strcmp(doiBong[i].maCT, key) == 0)
            {
                khop = 1;
            }
        }
        else
        {
            strcpy(chuoi, doiBong[i].hoTen);
            for (j = 0; chuoi[j] != '\0'; j++)
            {
                chuoi[j] = (char)tolower((unsigned char)chuoi[j]);
            }
            if (strstr(chuoi, key) != NULL)
            {
                khop = 1;
            }
        }

        if (khop)
        {
            if (!thay)
            {
                inTieuDeBang();
            }
            inHangCauThu(doiBong[i]);
            thay = 1;
        }
    }

    if (!thay)
    {
        printf("Khong tim thay cau thu nao!\n");
    }
}

/* ===== CAP NHAT CAU THU: Enter = giu nguyen tung truong ===== */
void capNhatCauThu(void)
{
    int vt;
    char ma[10];
    char tamTen[50];
    int soMoi;
    float luongMoi;
    int ketQua;

    if (soLuong == 0)
    {
        printf("Danh sach dang trong!\n");
        return;
    }

    if (!nhapMa("Nhap ma cau thu can cap nhat (0 de huy): ", ma))
    {
        return;
    }
    vt = timViTriMa(ma);

    if (vt == -1)
    {
        printf("Khong tim thay cau thu co ma %s!\n", ma);
        return;
    }

    printf("Thong tin hien tai:\n");
    inTieuDeBang();
    inHangCauThu(doiBong[vt]);
    printf("Nhap thong tin moi (Enter de giu nguyen, ma cau thu khong doi):\n");

    ketQua = nhapTenGiuNguyen("Nhap ho ten moi: ", tamTen, 50);
    if (ketQua == -1)
    {
        printf("Da huy cap nhat.\n");
        return;
    }
    if (ketQua == 1)
    {
        strcpy(doiBong[vt].hoTen, tamTen);
    }

    /* Vi tri: chon 0 = giu nguyen, chon 1-4 = doi sang vi tri moi,
       Ctrl+Z = huy cap nhat */
    ketQua = nhapViTri(doiBong[vt].viTri);
    if (ketQua == -1)
    {
        printf("Da huy cap nhat.\n");
        return;
    }

    while (1)
    {
        ketQua = nhapSoGiuNguyen("Nhap so ao moi (1-99): ", 1, 99, &soMoi);
        if (ketQua == -1)
        {
            printf("Da huy cap nhat.\n");
            return;
        }
        if (ketQua == 0)
        {
            break;
        }
        if (kiemTraSoAoTrung(soMoi, vt))
        {
            printf("So ao %d da co nguoi dung! Moi nhap lai.\n", soMoi);
            continue;
        }
        doiBong[vt].soAo = soMoi;
        break;
    }

    ketQua = nhapSoGiuNguyen("Nhap tuoi moi (16-45): ", 16, 45, &soMoi);
    if (ketQua == -1)
    {
        printf("Da huy cap nhat.\n");
        return;
    }
    if (ketQua == 1)
    {
        doiBong[vt].tuoi = soMoi;
    }

    ketQua = nhapSoGiuNguyen("Nhap so ban thang moi (0-980): ", 0, 980, &soMoi);
    if (ketQua == -1)
    {
        printf("Da huy cap nhat.\n");
        return;
    }
    if (ketQua == 1)
    {
        doiBong[vt].soBanThang = soMoi;
    }

    ketQua = nhapLuongGiuNguyen("Nhap luong tuan moi (trieu dong, 0-1000): ", &luongMoi);
    if (ketQua == -1)
    {
        printf("Da huy cap nhat.\n");
        return;
    }
    if (ketQua == 1)
    {
        doiBong[vt].luongTuan = luongMoi;
    }

    luuDuLieu();
    printf("Cap nhat cau thu thanh cong!\n");
}

/* ===== XOA CAU THU: co xac nhan y/n ===== */
void xoaCauThu(void)
{
    char ma[10];
    char dong[100];
    int vt, i;
    int ketQua;

    if (soLuong == 0)
    {
        printf("Danh sach dang trong!\n");
        return;
    }

    if (!nhapMa("Nhap ma cau thu can xoa (0 de huy): ", ma))
    {
        return;
    }
    vt = timViTriMa(ma);

    if (vt == -1)
    {
        printf("Khong tim thay cau thu co ma %s!\n", ma);
        return;
    }

    printf("Thong tin cau thu se bi xoa:\n");
    inTieuDeBang();
    inHangCauThu(doiBong[vt]);

    while (1)
    {
        ketQua = nhapDong("Ban co chac chan muon xoa? (y/n): ", dong, 100);
        if (ketQua == 0)
        {
            printf("Da huy xoa.\n");
            return;
        }
        if (ketQua == -1)
        {
            continue;
        }

        xoaKhoangTrang(dong);
        if (dong[0] != '\0')
        {
            char c = (char)tolower((unsigned char)dong[0]);
            if (c == 'y')
            {
                break;
            }
            if (c == 'n')
            {
                printf("Da huy xoa.\n");
                return;
            }
        }
        printf("Vui long nhap y (xoa) hoac n (huy).\n");
    }

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

    inTieuDeBang();
    for (i = 0; i < soLuong; i++)
    {
        inHangCauThu(doiBong[i]);
    }
}

/* ===== MINH: THONG KE ===== */
void thongKe(void)
{
    int tongBanThang = 0;
    float tongLuong = 0;
    int maxBanThang;
    int i;

    if (soLuong == 0)
    {
        printf("Danh sach trong!\n");
        return;
    }

    maxBanThang = doiBong[0].soBanThang;

    for (i = 0; i < soLuong; i++)
    {
        tongBanThang += doiBong[i].soBanThang;
        tongLuong += doiBong[i].luongTuan;
        if (doiBong[i].soBanThang > maxBanThang)
        {
            maxBanThang = doiBong[i].soBanThang;
        }
    }

    printf("%-24s %s\n", "Chi tieu", "Gia tri");
    printf("--------------------------------------------\n");
    printf("%-24s %d\n", "Tong so ban thang", tongBanThang);
    printf("%-24s %.1f trieu dong\n", "Tong quy luong/tuan", tongLuong);
    printf("%-24s %.1f trieu dong/tuan\n", "Luong trung binh", tongLuong / soLuong);

    if (maxBanThang == 0)
    {
        printf("Vua pha luoi: chua co ai ghi ban\n");
        return;
    }
    printf("Vua pha luoi (%d ban thang):\n", maxBanThang);
    inTieuDeBang();
    for (i = 0; i < soLuong; i++)
    {
        if (doiBong[i].soBanThang == maxBanThang)
        {
            inHangCauThu(doiBong[i]);
        }
    }
}

/* ===== MINH: SAP XEP ===== */
void sapXep(void)
{
    int i, j;

    if (soLuong == 0)
    {
        printf("Danh sach trong!\n");
        return;
    }

    /* Giam dan theo so ban thang; bang nhau thi theo ma tang dan */
    for (i = 0; i < soLuong - 1; i++)
    {
        for (j = i + 1; j < soLuong; j++)
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

    /* Luu thu tu moi xuong file de lan mo sau khop voi man hinh */
    luuDuLieu();
    printf("Da sap xep theo so ban thang giam dan (bang nhau thi theo ma).\n");
    hienThiDanhSach();
}

/* ===== MINH: LOC CAU THU ===== */
void locCauThu(void)
{
    int chon;
    int i;
    int soKetQua = 0;

    if (soLuong == 0)
    {
        printf("Danh sach trong!\n");
        return;
    }

    printf("Chon vi tri can loc:\n");
    printf("1. Tien dao\n2. Tien ve\n3. Hau ve\n4. Thu mon\n0. Quay lai menu\n");
    if (!nhapSo("Nhap lua chon (0-4): ", 0, 4, &chon))
    {
        return;
    }
    if (chon == 0)
    {
        return;
    }

    for (i = 0; i < soLuong; i++)
    {
        if (strcmp(doiBong[i].viTri, tenViTri(chon)) == 0)
        {
            if (soKetQua == 0)
            {
                inTieuDeBang();
            }
            inHangCauThu(doiBong[i]);
            soKetQua++;
        }
    }

    if (soKetQua == 0)
    {
        printf("Khong co cau thu nao o vi tri %s!\n", tenViTri(chon));
    }
}
