# oss_02_20251117
오픈소스 SW개론 실습 테스트
* 레파지토리 이름은 레파지토리가 생성된 날짜입니다.
---

```shell
ls -al
```

```python
import pandas as pd
import matplotlib.pyplot as plt
x = [3000, 4200, 4000, 5000, 6000, 3800, 3500, 6200, 3900, 4500]
y = [60, 75, 70, 85, 90, 70, 65, 95, 70, 80]
data = {'x': x, 'y': y}
df = pd.DataFrame(data)
plt.scatter(df['x'], df['y'])
plt.show( )
```

1. a
2. b
3. c

> 인용구

|Col1 |Col2    |
|-----|:------:|
|1    |2       |
