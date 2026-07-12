def bagi_array(arr, kiri, kanan):
    pivot = arr[kanan]   # pivot diambil dari elemen terakhir
    penanda = kiri - 1   # penanda posisi elemen kecil

    for j in range(kiri, kanan):
        if arr[j] <= pivot:
            penanda += 1
            arr[penanda], arr[j] = arr[j], arr[penanda]

    # tempatkan pivot di posisi yang tepat
    arr[penanda + 1], arr[kanan] = arr[kanan], arr[penanda + 1]

    return penanda + 1


def quick_sort(arr, kiri, kanan):
    if kiri < kanan:
        posisi_pivot = bagi_array(arr, kiri, kanan)

        # rekursif kiri dan kanan
        quick_sort(arr, kiri, posisi_pivot - 1)
        quick_sort(arr, posisi_pivot + 1, kanan)


# Contoh data ongkir
data_ongkir = [15000, 5000, 20000, 10000, 8000]

quick_sort(data_ongkir, 0, len(data_ongkir) - 1)

print("Data ongkir setelah diurutkan:")
print(data_ongkir)