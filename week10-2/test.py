from concurrent.futures import ThreadPoolExecutor
import requests
import time

url = "https://106.15.74.204"  # 替换为你测试的 URL

total_requests = 1000  # 根据需要调整请求数量
concurrent_threads = 100  # 设置并发线程数

def send_request():
    try:
        response = requests.get(url, timeout=10, verify=False)  # 增加超时并禁用 SSL 验证
        print(f"Status: {response.status_code}, Time: {response.elapsed.total_seconds()}s")
    except requests.RequestException as e:
        print(f"Request failed: {e}")

start_time = time.time()
with ThreadPoolExecutor(max_workers=concurrent_threads) as executor:
    futures = [executor.submit(send_request) for _ in range(total_requests)]
    for future in futures:
        future.result()  # 等待所有请求完成

end_time = time.time()
print(f"Test completed in {end_time - start_time:.2f} seconds.")
