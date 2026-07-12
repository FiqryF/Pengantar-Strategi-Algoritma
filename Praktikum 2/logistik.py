import time

def proses_logistik(berat, list_vendor):
    print("=== Memulai Proses Pengiriman ===")

    # Cari vendor termurah (Brute Force)
    vendor_terbaik = list_vendor[0]
    print(f"Total vendor yang dicek: {len(list_vendor)}")

    for v in list_vendor:
        if v["harga"] < vendor_terbaik["harga"]:
            vendor_terbaik = v

    total_biaya = vendor_terbaik["harga"] * berat

    print(f"Vendor terpilih: {vendor_terbaik['nama']}")
    print(f"Total biaya: Rp{total_biaya}")

    # Simulasi pembayaran
    print("Menghubungkan ke SmartBank...")
    time.sleep(1)
    status_bayar = True

    # Update status
    if status_bayar:
        status = "Pembayaran berhasil, pesanan diproses"
        print(f"Status: {status}")

    return {
        "vendor": vendor_terbaik["nama"],
        "biaya": total_biaya,
        "status": status
    }


# Data vendor
data_vendor = [
    {"nama": "Logistik_A", "harga": 15000},
    {"nama": "Logistik_B", "harga": 12000},
    {"nama": "Logistik_C", "harga": 18000},
    {"nama": "Logistik_D", "harga": 13500}
]

# Eksekusi
hasil = proses_logistik(berat=2, list_vendor=data_vendor)