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
    //printf("Chua trien khai\n");

    int kieu, c, i, j, k, len, hopLe, khop, thay = 0;
    char key[100], chuoi[50];

    if (soLuong == 0)
    {
        printf("Danh sach dang trong!\n");
        return;
    }

    /* Chon kieu tim: bat nhap lai neu khong phai 1 hoac 2 */
    do
    {
        printf("1. Tim theo ma\n2. Tim theo ten\nChon: ");
        if (scanf("%d", &kieu) != 1)
        {
            kieu = 0;
        }
        while ((c = getchar()) != '\n' && c != EOF);
        if (kieu != 1 && kieu != 2)
        {
            printf("Chi duoc nhap 1 hoac 2!\n");
        }
    }
    while (kieu != 1 && kieu != 2);

    /* Nhap tu khoa: kiem tra ky tu va khoang trang, sai thi nhap lai */
    do
    {
        hopLe = 1;
        printf("Nhap tu khoa: ");
        if (fgets(key, sizeof(key), stdin) == NULL)
        {
            return;
        }
        len = strlen(key);
        if (key[len - 1] == '\n')
        {
            key[--len] = '\0';
        }
        else
        {
            while ((c = getchar()) != '\n' && c != EOF);  /* nhap qua dai */
            hopLe = 0;
        }

        if (len == 0)
        {
            hopLe = 0;
        }
        else if (key[0] == ' ' || key[len - 1] == ' ')
        {
            hopLe = 0;  /* khoang trang o dau hoac cuoi */
        }

        for (j = 0; j < len && hopLe; j++)
        {
            if (key[j] == ' ')
            {
                if (kieu == 1 || key[j + 1] == ' ')
                {
                    hopLe = 0;  /* ma khong co khoang trang, ten khong co 2 khoang trang lien tiep */
                }
            }
            else if (!((key[j] >= 'a' && key[j] <= 'z') || (key[j] >= 'A' && key[j] <= 'Z')))
            {
                if (kieu == 2 || key[j] < '0' || key[j] > '9')
                {
                    hopLe = 0;  /* ten chi chu cai; ma chi chu cai va so */
                }
            }
        }

        if (!hopLe)
        {
            if (kieu == 1)
            {
                printf("Nhap sai! Chi nhap chu cai (hoa hoac thuong) va so, khong co khoang trang.\n");
            }
            else
            {
                printf("Nhap sai! Chi nhap chu cai (hoa hoac thuong), cach nhau dung 1 khoang trang.\n");
            }
        }
    }
    while (!hopLe);

    /* Doi tu khoa thanh chu thuong */
    for (j = 0; key[j]; j++)
    {
        if (key[j] >= 'A' && key[j] <= 'Z')
        {
            key[j] = key[j] + 32;
        }
    }

    /* Duyet danh sach, so sanh khong phan biet hoa thuong */
    for (i = 0; i < soLuong; i++)
    {
        if (kieu == 1)
        {
            strcpy(chuoi, doiBong[i].maCT);
        }
        else
        {
            strcpy(chuoi, doiBong[i].hoTen);
        }
        for (k = 0; chuoi[k]; k++)
        {
            if (chuoi[k] >= 'A' && chuoi[k] <= 'Z')
            {
                chuoi[k] = chuoi[k] + 32;
            }
        }

        khop = 0;
        if (kieu == 1 && strcmp(chuoi, key) == 0)
        {
            khop = 1;  /* ma: khop chinh xac */
        }
        if (kieu == 2 && strstr(chuoi, key) != NULL)
        {
            khop = 1;  /* ten: chi can chua tu khoa */
        }

        if (khop == 1)
        {
            printf("%s | %s | %s | ao so %d | %d tuoi | %d ban | luong %.1f trieu/tuan\n",
                   doiBong[i].maCT, doiBong[i].hoTen, doiBong[i].viTri,
                   doiBong[i].soAo, doiBong[i].tuoi, doiBong[i].soBanThang,
                   doiBong[i].luongTuan);
            thay = 1;
        }
    }
    if (thay == 0)
    {
        printf("Khong tim thay cau thu nao!\n");
    }
}

//�ang tai phan code chuc nang cap nhat cau thu , neu doc toi day thi la dang xu ly cac phan khai bao

	void boKyTuThua(void)
		{
		    int c;
		    while ((c = getchar()) != '\n' && c != EOF);
		}

	int nhapMa(const char thongBao[], char ma[])
		{
		    printf("%s", thongBao);

		    if (scanf("%9s", ma) != 1)
		        return 0;

		    boKyTuThua();
		    return 1;
		}
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
	int nhapTen(const char thongBao[], char ten[], int kichThuoc)
		{
		    printf("%s", thongBao);

		    if (fgets(ten, kichThuoc, stdin) == NULL)
		        return 0;

		    ten[strcspn(ten, "\n")] = '\0';

		    return 1;
		}
	int nhapSo(const char thongBao[], int min, int max, int *so)
		{
		    printf("%s", thongBao);

		    if (scanf("%d", so) != 1)
		    {
		        int c;
		        while ((c = getchar()) != '\n' && c != EOF);
		        return 0;
		    }

		    if (*so < min || *so > max)
		    {
		        printf("Gia tri khong hop le!\n");
		        return 0;
		    }

		    return 1;
		}
	int nhapLuong(const char thongBao[], float *luong)
		{
		    printf("%s", thongBao);

		    if (scanf("%f", luong) != 1)
		    {
		        int c;
		        while ((c = getchar()) != '\n' && c != EOF);
		        return 0;
		    }

		    if (*luong < 0)
		    {
		        printf("Luong khong duoc am!\n");
		        return 0;
		    }

		    return 1;
		}

void capNhatCauThu()
{
    //printf("Chua trien khai\n");
      int vt, soAo, tuoi, soBanThang;
    float luong;
    char ma[100], hoTen[50], viTri[20];

    if (soLuong == 0)
    {
        printf("Danh sach dang trong!\n");
        return;
    }
    boKyTuThua();

    if (nhapMa("Nhap ma cau thu can cap nhat: ", ma) == 0)
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
    inThongTinCauThu(doiBong[vt]);

    printf("Nhap thong tin moi (ma cau thu khong doi):\n");

    if (nhapTen("Nhap ho ten: ", hoTen, 50) == 0)
        return;

    if (nhapTen("Nhap vi tri: ", viTri, 20) == 0)
        return;

    if (nhapSo("Nhap so ao (1-99): ", 1, 99, &soAo) == 0)
        return;

    if (nhapSo("Nhap tuoi (16-45): ", 16, 45, &tuoi) == 0)
        return;

    if (nhapSo("Nhap so ban thang (>= 0): ", 0, 999, &soBanThang) == 0)
        return;

    if (nhapLuong("Nhap luong tuan (trieu dong, >= 0): ", &luong) == 0)
        return;

    strcpy(doiBong[vt].hoTen, hoTen);
    strcpy(doiBong[vt].viTri, viTri);
    doiBong[vt].soAo = soAo;
    doiBong[vt].tuoi = tuoi;
    doiBong[vt].soBanThang = soBanThang;
    doiBong[vt].luongTuan = luong;

    printf("Cap nhat cau thu thanh cong!\n");
}

void xoaCauThu()
{
   // printf("Chua trien khai\n");
   char ma[100];
    int vt, i;

    if (soLuong == 0)
    {
        printf("Danh sach dang trong!\n");
        return;
    }

    boKyTuThua();

    if (nhapMa("Nhap ma cau thu can xoa: ", ma) == 0)
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
    inThongTinCauThu(doiBong[vt]);

    for (i = vt; i < soLuong - 1; i++)
    {
        doiBong[i] = doiBong[i + 1];
    }

    soLuong--;

    printf("Xoa cau thu thanh cong!\n");
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
    printf("Chua trien khai\n");
}

void sapXep()
{
    printf("Chua trien khai\n");
}

void locCauThu()
{
    printf("Chua trien khai\n");
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
