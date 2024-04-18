import random

def coin_flip():
    
    coinflip = random.randint(0,1)
    if coinflip == 0:
        result = "Tails"
    else:
        result = "Heads"
        
    return result
            


if __name__ == '__main__':
    random.seed(5)  # Unique seed
    number_of_flips = int(input())

    for i in range(number_of_flips):
        print(coin_flip())
