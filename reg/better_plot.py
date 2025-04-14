import os
import pandas as pd
import matplotlib
import matplotlib.pyplot as plt

matplotlib.use('agg')  # No GUI backend

plik_danych = 'result_creg.csv'
plik_obrazu = 'plot_creg.png'
plik_widoku = 'plot_result.html'

if not os.path.isfile(plik_danych):
    print('Brak pliku danych.')
    exit()

df = pd.read_csv(plik_danych)
df.columns = df.columns.str.strip()

required_cols = {'Wsp. x', 'Wsp. y1', 'Wsp. y2'}
if not required_cols.issubset(df.columns):
    print("Brak wymaganych kolumn. Zawarte kolumny:", df.columns.tolist())
    exit()

x = df['Wsp. x']
y1 = df['Wsp. y1']
y2 = df['Wsp. y2']

# Rysowanie wykresu
plt.figure(figsize=(12, 6))
plt.xticks(fontsize=14)
plt.yticks(fontsize=14)
plt.title("Przebieg", fontsize=14)
plt.xlabel('Czas [s]', fontsize=14)
plt.ylabel("Temperatura [C]", fontsize=14)
plt.plot(x, y1, color='#ff0000', label='Regulator', linewidth=2)
plt.plot(x, y2, color='#0000aa', label='Wyjście', linewidth=2)#linestyle='', marker=".", markersize=2)
plt.grid(color='#888888', linestyle='-')
plt.legend(loc='upper right')
plt.savefig(plik_obrazu)

# Tworzenie prostego pliku HTML z obrazkiem
if not os.path.isfile(plik_widoku):
    with open(plik_widoku, 'w') as f:
        f.write(f'''
        <html>
            <head><title>Wykres</title></head>
            <body>
                <h1>Wykres z pliku danych</h1>
                <img src="{plik_obrazu}" alt="Wykres" style="max-width:100%;">
            </body>
        </html>
        ''')


print(f'Gotowe! Otwórz plik {plik_widoku} w przeglądarce.')