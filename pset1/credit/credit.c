#include <cs50.h>
#include <stdio.h>

int getLength(long len);
int timesTwoSum(long cardNum2, int cardLength);
int sumOtherDigits(long cardNum2, int cardLength);
int cardType(long cardNum, int cardLength);

int main(void)
{
    long cardNum2;
    long cardNum;
    do
    {
    cardNum = get_long("Enter Card Number\n");
    }
    while (cardNum < 0);
    int cardLength = getLength(cardNum);
    if (cardLength > 13 && cardLength < 19)
    {
        cardNum2 = cardNum / 10; //remove last digit
        int multipyTwoSum = timesTwoSum(cardNum2, cardLength);
        //printf("%i\n", multipyTwoSum);
        int otherDigitsSum = sumOtherDigits(cardNum, cardLength);
        //printf("%i\n", otherDigitsSum);
        if ((multipyTwoSum + otherDigitsSum) % 10 == 0)
        {
            int cardTypeChoice = cardType(cardNum,cardLength);
            if (cardTypeChoice == 34 || cardTypeChoice == 37)
            {
                printf("AMEX\n");
            }
            else if (cardTypeChoice > 50 && cardTypeChoice <= 55)
            {
                printf("MASTERCARD\n");
            }
            else if (cardTypeChoice >= 40 && cardTypeChoice <=49 )
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else {
        printf("INVALID\n");
    }
}

int cardType(long card,int length){
    int crop = length - 2;
    for(int i = 0; i < crop; i++){
        card = card / 10;
    }
    return card;
}

int sumOtherDigits(long card, int length){
    int total = 0;
    for(int i=0; i<length; i++){
        int digit = card%10;
        card = card/100;
        total=total+digit;
    }
    return total;
}


int timesTwoSum(long card, int length){
    int total = 0;
    int popped = 0;
    for(int i=1; i<length; i++){
        int digit = card%10;
        card = card/100;
        if(digit>=5){
            total=total+((digit*2)%10)+1;
        }
        else{
            total = total+(digit*2);
        }
        //printf("%i\n", digit);

    }
    return total;
}

int getLength(long card){
    int count=0;
    while(card>0){
        card=card/10;
        count=count+1;
    }
    return count;
}

