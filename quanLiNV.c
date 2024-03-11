
#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include <string.h>
#include <stdlib.h>

struct NhanVien {
	char maNhanVien[9];
	char tenNhanVien[21];
   char tinhTrangGiaDinh[2];
   unsigned char soCon;
   char trinhDoVanHoa[3];
   unsigned int luongCanBan;
   unsigned char nghiCoPhep;
   unsigned char nghiKhongPhep;
   unsigned char ngayLamThem;
   char ketQuaCongViec[3];
   float luongThuongLinh;
};

void nhapNhanVien(struct NhanVien *nv) {
	printf("\nNhap ma so nhan vien (8 ki tu): ");
	scanf("%s", &nv->maNhanVien);
	printf("Nhap ho va ten (Toi da 20 ki tu): ");
	fflush(stdin);
	gets(nv->tenNhanVien);
   printf("Tinh trang gia dinh (1 ki tu; M = Married; S = Singel): ");
	fflush(stdin);
   gets(nv->tinhTrangGiaDinh);
   printf("So con (Nho hon 20): ");
	fflush(stdin);
   scanf("%d", &nv->soCon);
   printf("Trinh do van hoa (2 ki tu; C1=cap1; C2=cap2; C3=cap3; DH=DaiHoc; CH=CaoHoc): ");
	fflush(stdin);
   gets(nv->trinhDoVanHoa);
   printf("Luong can ban (<=1000000): ");
	fflush(stdin);
   scanf("%d", &nv->luongCanBan);
   printf("So ngay nghi co phep (<=28): ");
	fflush(stdin);
   scanf("%d", &nv->nghiCoPhep);
   printf("So ngay nghi khong phep (<=28): ");
	fflush(stdin);
   scanf("%d", &nv->nghiKhongPhep);
   printf("So ngay lam them (<=28): ");
	fflush(stdin);
   scanf("%d", &nv->ngayLamThem);
   printf("Ket qua cong viec (T=Tot; TB=Dat; K=Kem): ");
	fflush(stdin);
   gets(nv->ketQuaCongViec);
   float phuTroi = 0;
   if (nv->soCon > 2) phuTroi += 0.05*nv->luongCanBan;
   if (strcmp(nv->trinhDoVanHoa, "CH")==0) phuTroi += 0.1*nv->luongCanBan;
   if (nv->ngayLamThem > 0) phuTroi += 0.04*nv->luongCanBan;
   if (nv->nghiKhongPhep > 0) phuTroi -=0.05*nv->luongCanBan;
   nv->luongThuongLinh = nv->luongCanBan +  phuTroi;
}

void nhapDanhSachNhanVien(struct NhanVien nv[], int *n) {
	printf("\nNhap so nhan vien: ");
	scanf("%d", n);
	for (int i = 0; i < *n; i++)
	{
		printf("\nNhan vien thu %d ", i + 1);
		nhapNhanVien(&nv[i]);
	}
}

void xuatNhanVien(struct NhanVien nv) {
   printf("%12s%20s%15s%8d%10s%10d%10d%14d%10d%14s%10.0f",
   nv.maNhanVien, 
   nv.tenNhanVien, 
   nv.tinhTrangGiaDinh, 
   nv.soCon, 
   nv.trinhDoVanHoa,
   nv.luongCanBan,
   nv.nghiCoPhep,
   nv.nghiKhongPhep,
   nv.ngayLamThem,
   nv.ketQuaCongViec,
   nv.luongThuongLinh);

}

void xuatDanhSachNhanVien(struct NhanVien nv[], int n) {
	printf("\n%12s%20s%15s%8s%10s%10s%10s%14s%10s%14s%10s\n", 
      "MA_NHAN_VIEN", 
      "HO_TEN", 
      "TINH_TRANG_GD", 
      "SO_CON", 
      "TRINH_DO",
      "LUONG_CB",
      "NGHI_PHEP",
      "NGHI_K_PHEP",
      "LAM_THEM",
      "KQ_CONG_VIEC",
      "LUONG"
   );

	for (int i = 0; i < n; i++)
	{
		xuatNhanVien(nv[i]);
		printf("\n");
	}
}

void xuatMotNhanVien(struct NhanVien nv[], int viTri) {
   struct NhanVien oneNV[1];
   oneNV[0] = nv[viTri];
   xuatDanhSachNhanVien(oneNV, 1);
}

int timNhanVien(struct NhanVien nv[], int n, char maNhanVien[]) {
	for (int i = 0; i < n; i++)
	{
		if (strcmp(nv[i].maNhanVien, maNhanVien) == 0) return i;
	}
	return -1;
}

void chinhSuaNhanVien(struct NhanVien nv[], int n) {
   if (n==0) {
      printf("\nDanh sach khong co sinh vien!");
   } else {
      char maNhanVien[9];
      printf("\nNhap ma nhan vien (8 ki tu): ");
      fflush(stdin);
	   gets(maNhanVien);
      int viTri = timNhanVien(nv, n, maNhanVien);
      if (viTri == -1) {
         printf("\nKhong tim thay nhan vien trong danh sach");
      } else {   
         printf("\nBan hay nhap lai thong tin nhan vien\n");
         nhapNhanVien(&nv[viTri]);
         printf("\nBan da cap nhat thanh cong %s!", maNhanVien);
      }     
   }
}

void themNhanVien(struct NhanVien nv[], int *n) {
	if (*n == 50) {
		printf("\nDanh sach da full!");
	} else {
      printf("\nNhap thong tin nhan vien can them ");
		nhapNhanVien(&nv[*n]);
		(*n)++; // de trong dau ngoac de cong gia tri tai o nho con tro tro toi
	}
}

void xoaNhanVien(struct NhanVien nv[], int *n) {
	if (*n == 0) {
		printf("\nDanh sach khong co sinh vien!");
	} else {
	   char maNhanVien[9];
		printf("\nNhap ma so nhan vien can xoa: ");
      fflush(stdin);
		gets(maNhanVien);
		int viTri = timNhanVien(nv, *n, maNhanVien);
		if (viTri == -1) {
			printf("\nKhong tim thay nhan vien!");
		} else {
			printf("\nThong sinh sinh vien da xoa: \n");
			xuatMotNhanVien(nv, viTri);
			for (int i = viTri; i < *n - 1; i++) {
				nv[i] = nv[i + 1];
			}
			(*n)--;
		}
	}
}

void timThongTinNhanVien(struct NhanVien nv[], int n) {
   if(n == 0) {
      printf("\nDanh sach khong co nhan vien nao!");
   } else {
      char maNhanVien[9];
      printf("\nNhap ma so nhan vien can tim thong tin: ");
      fflush(stdin);
		gets(maNhanVien);
		int viTri = timNhanVien(nv, n, maNhanVien);
      if (viTri == -1) {
         printf("\nKhong tim thay nhan vien trong danh sach.");
      } else {
         printf("\nThong tin nhan vien can tim: \n");
         xuatMotNhanVien(nv, viTri);
         // NhanVien oneNV[1];
         // oneNV[0] = nv[viTri];
         // xuatDanhSachNhanVien(oneNV, 1);
      }
   }
}

void xemBangLuongNhanVien(struct NhanVien nv[], int n) {
   printf("\n%12s%20s%10s%10s%14s%10s%14s%10s\n", 
      "MA_NHAN_VIEN", 
      "HO_TEN", 
      "LUONG_CB",
      "NGHI_PHEP",
      "NGHI_K_PHEP",
      "LAM_THEM",
      "KQ_CONG_VIEC",
      "LUONG"
   );
   for (int i = 0; i < n; ++i) {
      printf("%12s%20s%10d%10d%14d%10d%14s%10.0f\n",
      nv[i].maNhanVien, 
      nv[i].tenNhanVien, 
      nv[i].luongCanBan,
      nv[i].nghiCoPhep,
      nv[i].nghiKhongPhep,
      nv[i].ngayLamThem,
      nv[i].ketQuaCongViec,
      nv[i].luongThuongLinh);
   }
}

void swap(struct NhanVien *a, struct NhanVien *b) {
   struct NhanVien temp;
   temp = *a;
   *a = *b;
   *b = temp;
}

void SelectionSort(struct NhanVien nv[], int n) {
      int min;
      for (int i = 0; i < n - 1; ++i) {
         min = i;
         for (int j = i + 1; j < n; ++j) {
            if (nv[j].luongThuongLinh < nv[min].luongThuongLinh) {
               min = j;
            }
            if(min != i) swap(&nv[min], &nv[i]);
         }
      }
}

void xuatFile(struct NhanVien nv[], int n) {
   // char tenFile[100];
   // printf("\nNhap ten file: ");
   // fflush(stdin);
   // gets(tenFile);
   
   FILE *f;
   f = fopen("DSNhanVien.bin", "wb");
   if (f == NULL) {
      printf("\nLoi moi file de ghi!");
      return;
   }
   fwrite(&n, sizeof(n), 1, f);
   for (int i = 0; i < n; ++i) {
      fwrite(&nv[i], sizeof(nv[i]), 1, f);
   }
   fclose(f);
   printf("\nBan da xuat vao file thanh cong!");
}

void docFile(struct NhanVien nv[], int *n) {
   //    char tenFile[50];
   // printf("\nNhap ten file: ");
   // fflush(stdin);
   // gets(tenFile);
   FILE *f;
   f = fopen("DSNhanVien.bin", "rb");
   if (f == NULL) {
      printf("\nLoi moi file de doc!");
      return;
   }
   fread(n, sizeof(*n), 1, f);
   for (int i = 0; i < *n; ++i) {
      fread(&nv[i], sizeof(struct NhanVien), 1, f);
   }
   fclose(f);
   printf("\nBan doc tu file thanh cong!");
}

int main() {
	int N=0;
	struct NhanVien NV[50];
	int option;
	do
	{ 
      printf("\n==========================================");
		printf("\n**********MENU QUAN LI NHAN VIEN**********\n");
		printf("1. Nhap danh sach \n");
		printf("2. Xuat danh sach\n");
		printf("3. Them\n");
		printf("4. Chinh sua\n");
		printf("5. Xoa\n");
		printf("6. Xem bang luong nhan vien\n");
		printf("7. Tim thong tin mot nhan vien\n");																																																																							
		printf("8. Xuat danh sach nhan vien vao file\n");																																																																							
		printf("9. Doc danh sach nhan vien tu file\n");	
      printf("10. Sắp xếp theo lương\n");																																																																						
		printf("0. Thoat\n");
		printf("Nhap lua chon: ");
		scanf("%d", &option);
		switch (option)
		{
		case 1:
			nhapDanhSachNhanVien(NV, &N);
         printf("\nNhan phim bat ki de thoat...");
         getch();
			break;
		case 2:
			xuatDanhSachNhanVien(NV, N);
         printf("\nNhan phim bat ki de thoat...");
         getch();
			break;
		case 3:
			themNhanVien(NV, &N);
         printf("\nNhan phim bat ki de thoat...");
         getch();
			break;
		case 4:
			chinhSuaNhanVien(NV, N);
         printf("\nNhan phim bat ki de thoat...");
         getch();
			break;
		case 5:
			xoaNhanVien(NV, &N);
         printf("\nNhan phim bat ki de thoat...");
         getch();
			break;
		case 6:
			xemBangLuongNhanVien(NV, N);
         printf("\nNhan phim bat ki de thoat...");
         getch();
			break;
		case 7:
			timThongTinNhanVien(NV, N);
			printf("\nNhan phim bat ki de thoat...");
         getch();
			break;
      case 8:
         xuatFile(NV, N);
         printf("\nNhan phim bat ki de thoat...");
         getch();
         break;  
      case 9:
         docFile(NV, &N);
         printf("\nNhan phim bat ki de thoat...");
         getch();
         break;
      case 10:
         SelectionSort(NV, N);
         printf("\nNhan phim bat ki de thoat...");
         getch();
         break;
      default:
         break;
      }
	} while (option != 0);	
   return 0;
}