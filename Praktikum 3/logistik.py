def greedy_loading(kapasitas, paket_list):

    # Hitung rasio nilai/berat
    for item in paket_list:
        item["rasio"] = item["biaya"] / item["berat"]

    # Urutkan dari rasio terbesar
    paket_list.sort(key=lambda x: x["rasio"], reverse=True)

    total_berat = 0
    total_nilai = 0
    paket_terpilih = []

    print(f"=== Proses Greedy Loading (Kapasitas {kapasitas} kg) ===")

    for item in paket_list:
        if total_berat + item["berat"] <= kapasitas:
            total_berat += item["berat"]
            total_nilai += item["biaya"]
            paket_terpilih.append(item["nama"])

            print(f"Ambil {item['nama']} (berat: {item['berat']} kg, nilai: {item['biaya']})")
        else:
            print(f"Lewati {item['nama']} (tidak cukup kapasitas)")

    return paket_terpilih, total_nilai


# Data paket
data_paket = [
    {"nama": "Paket_A", "berat": 3, "biaya": 50000},
    {"nama": "Paket_B", "berat": 5, "biaya": 60000},
    {"nama": "Paket_C", "berat": 2, "biaya": 40000},
    {"nama": "Paket_D", "berat": 1, "biaya": 15000}
]

# Eksekusi
hasil, total = greedy_loading(10, data_paket)

print(f"\nKesimpulan: Paket yang dipilih {hasil} dengan total keuntungan Rp{total}")