#include <stdio.h>
#include <string.h>

/* ===== STRUCT (da chot) ===== */
typedef struct
{
    char maCT[10];      // "CT001" - khoa chinh de tim/sua/xoa
    char hoTen[50];
    char viTri[20];     // "Tien dao", "Tien ve", "Hau ve", "Thu mon"
    int soAo;           // 1 - 99
    int tuoi;           // 16 - 45
    int soBanThang;     // >= 0
    float luongTuan;    // >= 0, don vi: trieu dong/tuan
} CauThu;

/* ===== BIEN TOAN CUC ===== */
CauThu doiBong[100];
int soLuong = 0;
int kiemTraMaTrung(char maCanKiem[]);
/* ===== Quan ===== */
void themCauThu()
{
    if (soLuong >= 100)
    {
        printf("Danh sach da day\n");
        return;
    }

    CauThu moi;

    do
    {
        printf("Nhap ma cau thu (VD: CT001): ");
        scanf("%9s", moi.maCT);
        if (kiemTraMaTrung(moi.maCT) == 1)
        {
            printf("Ma da ton tai! Moi nhap lai.\n");
        }
    }
    while (kiemTraMaTrung(moi.maCT) == 1);

    printf("Nhap ho ten: ");
    scanf(" %49[^\n]", moi.hoTen);

    printf("Nhap vi tri: ");
    scanf(" %19[^\n]", moi.viTri);

    do
    {
        printf("Nhap so ao (1-99): ");
        scanf("%d", &moi.soAo);
        if (moi.soAo < 1 || moi.soAo > 99)
        {
            printf("So ao phai tu 1 den 99! Moi nhap lai.\n");
        }
    }
    while (moi.soAo < 1 || moi.soAo > 99);

    do
    {
        printf("Nhap tuoi (16-45): ");
        scanf("%d", &moi.tuoi);
        if (moi.tuoi < 16 || moi.tuoi > 45)
        {
            printf("Tuoi phai tu 16 den 45! Moi nhap lai.\n");
        }
    }
    while (moi.tuoi < 16 || moi.tuoi > 45);

    do
    {
        printf("Nhap so ban thang (>= 0): ");
        scanf("%d", &moi.soBanThang);
        if (moi.soBanThang < 0)
        {
            printf("So ban thang khong duoc am! Moi nhap lai.\n");
        }
    }
    while (moi.soBanThang < 0);

    do
    {
        printf("Nhap luong tuan (trieu dong, >= 0): ");
        scanf("%f", &moi.luongTuan);
        if (moi.luongTuan < 0)
        {
            printf("Luong tuan khong duoc am! Moi nhap lai.\n");
        }
    }
    while (moi.luongTuan < 0);

    doiBong[soLuong] = moi;
    soLuong++;
    printf("Them cau thu thanh cong!\n");

}

int kiemTraMaTrung(char maCanKiem[])
{
    for (int i = 0; i < soLuong; i++)
    {
        if (strcmp(doiBong[i].maCT, maCanKiem) == 0)
        {
            return 1;
        }
    }
    return 0;
}


/* ===== Long ===== */
void timKiemCauThu()
{
    printf("Chua trien khai\n");
}

void capNhatCauThu()
{
    printf("Chua trien khai\n");
}

void xoaCauThu()
{
    printf("Chua trien khai\n");
}

/* ===== Minh ===== */
void hienThiDanhSach()
{
        if (soLuong == 0)
    {
        printf("Danh sach trong!\n");
        return;
    }

    printf("%-8s%-20s%-10s%-8s%-6s%-11s%-8s\n", "Ma", "Ho ten", "Vi tri", "So ao", "Tuoi", "Ban thang", "Luong");
    printf("-----------------------------------------------------------------------\n");
    for (int i = 0; i < soLuong; i++)
    {
        printf("%-8s%-20s%-10s%-8d%-6d%-11d%-8.1f\n",
               doiBong[i].maCT, doiBong[i].hoTen, doiBong[i].viTri,
               doiBong[i].soAo, doiBong[i].tuoi, doiBong[i].soBanThang, doiBong[i].luongTuan);
    }
}

void thongKe()
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

void sapXep()
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

void locCauThu()
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

/* ===== HAM MAIN - menu (Quan) ===== */
int main()
{
    printf("Chuong trinh quan ly cau thu - struct da san sang!\n");
    int luaChon = 0;
    do
    {
        printf("1. Them cau thu moi\n");
        printf("2. Hien thi danh sach cau thu\n");
        printf("3. Tim kiem cau thu (theo ma / ten)\n");
        printf("4. Cap nhat thong tin cau thu (theo ma)\n");
        printf("5. Xoa cau thu (theo ma)\n");
        printf("6. Thong ke (tong ban thang, tong quy luong, luong trung binh, vua pha luoi)\n");
        printf("7. Sap xep\n");
        printf("8. Loc cau thu\n");
        printf("0. Thoat\n");
        printf("\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &luaChon);

        switch (luaChon)
        {
        case 1:
            themCauThu();
            break;
        case 2:
            hienThiDanhSach();
            break;
        case 3:
            timKiemCauThu();
            break;
        case 4:
            capNhatCauThu();
            break;
        case 5:
            xoaCauThu();
            break;
        case 6:
            thongKe();
            break;
        case 7:
            sapXep();
            break;
        case 8:
            locCauThu();
            break;
        case 0:
            printf("Chao tam biet\n");
            break;
        default:
            printf("Lua chon khong hop le!\n");
        }
    }
    while (luaChon != 0);
    return 0;
}
