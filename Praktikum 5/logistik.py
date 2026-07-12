def cari_order(data, target):
    kiri = 0
    kanan = len(data) - 1

    print(f"Mencari ID pesanan: {target}")

    while kiri <= kanan:
        tengah = (kiri + kanan) // 2
        nilai = data[tengah]

        print(f"Cek index {tengah} dengan nilai {nilai}")

        if nilai == target:
            return f"Order {target} ditemukan pada index {tengah}"

        elif nilai > target:
            kanan = tengah - 1
        else:
            kiri = tengah + 1

    return "Order tidak ditemukan"


# Data harus terurut
data_pesanan = [101, 105, 110, 115, 120, 125, 130]

target_id = 115

hasil = cari_order(data_pesanan, target_id)

print(hasil)