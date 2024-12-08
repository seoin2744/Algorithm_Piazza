currency_units = [50000, 10000, 5000, 1000, 500, 100, 50, 10]

def calculate_change(amount):
    change = {}  

    for unit in currency_units:
        count = amount // unit  
        if count > 0:
            change[unit] = count
        amount %= unit  

    return change

print("거스름돈 계산기 (한국 화폐 단위)")
try:
    amount = int(input("거스름돈으로 줄 금액을 입력하세요 (원): "))
    if amount <= 0:
        print("금액은 0원보다 커야 합니다!")
    else:
        change = calculate_change(amount)
        print("\n거스름돈:")
        for unit, count in change.items():
            print(f"{unit}원: {count}개")
except ValueError:
    print("올바른 금액을 입력하세요!")
