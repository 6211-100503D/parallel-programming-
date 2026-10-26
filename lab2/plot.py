import matplotlib.pyplot as plt

threads = [1, 2, 4, 8]
times = [0.0687616, 0.0749039, 0.0703965, 0.0707806]

plt.figure(figsize=(8, 5))
plt.plot(threads, times, 'bo-', linewidth=2, markersize=8)
plt.xlabel('Количество потоков')
plt.ylabel('Время (секунды)')
plt.title('Время выполнения умножения матриц 200x200')
plt.grid(True)
plt.xticks(threads)
plt.savefig('graph_time.png', dpi=150)
print("Сохранён graph_time.png")

speedup = [times[0] / t for t in times]
plt.figure(figsize=(8, 5))
plt.plot(threads, speedup, 'ro-', linewidth=2, markersize=8)
plt.plot(threads, threads, 'k--', label='Идеальное ускорение')
plt.xlabel('Количество потоков')
plt.ylabel('Ускорение (Speedup)')
plt.title('Ускорение параллельного умножения матриц')
plt.legend()
plt.grid(True)
plt.xticks(threads)
plt.savefig('graph_speedup.png', dpi=150)
print("Сохранён graph_speedup.png")
