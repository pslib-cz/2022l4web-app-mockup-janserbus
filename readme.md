# Web based RPG/strategie

Hráč bude spravovat vesnici, rozrůstat jí, sbýrat nové suroviny

## Začátek hry

Hra začíná se 12 lidmi a s 250 jednotkami potravin. Hráč bude přiřazovat volné lidi do práce, čímž bude generovat suroviny. Ze začaáku hry se bude jednat především o jednoduché suroviny a práce. Sběrači budou produkovat malé možství jídla, což bude znamenat, že pro uživení populace bude nezbytné aby většína lidí sbírala jídlo. Zbylích pár jedniců pak bude moci sbírat dřevo nebo kamení.

## Globální proměnné

1. rok = 40s - doporučené nastavení
2. populačníRůst = 0.05%/rok

## Zdroje

1. základní
   - Pracovní síla - využívá se k získání ostatních zdrojů
   - Dřevo - stavební materiál
   - Potraviny - nezbytné pro růst populace
2. Pokročilé zdroje:
   - Kámen

## Populace (Pracovní síla)

Růst populace bude modelován pomocí nasledující rovnice:

$P = P_0×e^{rt}$

kde:

- $P$ - konečný stav populace
- $P_0$ - současný stav populace
- $r$ - desetiné číslo vyjadřující procentuaní růst populace v daném čase (u lidské populace se jedná zhruba o 2% ročně)
- $t$ - čas

Populační růst se vypočítává pomocí následující rovnice:

$r =r×h$

- $h$ - koeficient štěstí a leží v intervalu $<-1;1>$ a zavisí na průměrném štěstí $h_a$
- pro $h_a=<0;20>$ se $h=-1;0>$
- pro $h_a=<20;80$ se $h=(0,1>$

### Třída jedinec

- __Happiness__ - hodnota mezi 0 - 100 určuje jak moc je jedinec šťastný
- __Hunger__ - hodnota mezi 0 - 100 určuje uroveň hladu
- __Housing__ - ukladá zda má jedinec kde bydlet
- __Work__ - ukládá typ práce, kterou daný jedinec zrovna provozuje
- __eat()__ - stará se o stav hladu daného jedince
- __work()__ - vyprodukuje suroviny v závislozti na práci

#### Happiness

__Štěstí__ bude ovlivněno __Hladem__, __Prací__ a __Ubytováním__. Pokud hlad klesne pod 70% stěstí začne klesat. Na 20% se spustí hladovění

## Suroviny

Speciální mechanika regulující jejich dostupnost

### Dřevo

### Kámen

## Budovy
