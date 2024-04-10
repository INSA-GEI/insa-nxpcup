import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import random

# Fonction pour générer les tableaux de données aléatoires
def generate_random_arrays(num_arrays, array_length):
    random_arrays = []
    for _ in range(num_arrays):
        random_array = [random.randint(0, 1023) for _ in range(array_length)]
        random_arrays.append(random_array)
    return random_arrays

# Nombre de tableaux à générer et leur longueur
num_arrays = 1
array_length = 128

# Générer les tableaux de données aléatoires
data = generate_random_arrays(num_arrays, array_length)

# Créer une figure et des sous-graphiques
fig, ax = plt.subplots()

# Initialiser les lignes du graphique avec des données vides
lines = [ax.plot([], [], label=f"Array {i+1}")[0] for i in range(num_arrays)]

# Fonction d'initialisation de l'animation
def init():
    for line in lines:
        line.set_data([], [])
    return lines

# Fonction de mise à jour des données à chaque image de l'animation
def update(frame):
    # Mettre à jour les données des tableaux à chaque actualisation
    data = generate_random_arrays(num_arrays, array_length)
    for i, line in enumerate(lines):
        line.set_data(range(len(data[i])), data[i][:frame])
    return lines

# Configurer les axes du graphique
ax.set_xlim(0, array_length)
ax.set_ylim(0, 1023)
ax.set_xlabel('Index')
ax.set_ylabel('Valeur')
ax.set_title('Tracé en temps réel des tableaux aléatoires')
ax.legend()

# Créer l'animation
ani = FuncAnimation(fig, update, frames=200, interval=100, blit=False)

# Afficher le graphique
plt.show()
