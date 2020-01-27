#include "./header_file/coins.h"

void deleteCoins(unsigned short int X, unsigned short int Y, cellXY **head, cellXY **tail, cell ***stage){
	if(*head==NULL){return;}
	(*stage)[X][Y].type = 0;
	if((*head)->X==X && (*head)->Y==Y){
		cellXY *temp = *head;
		*head = (*head)->next;
		free(temp);
		if(*head == NULL){*tail = NULL;}
		else{
			(*head)->prev = NULL;
		}
	}
	else{
		cellXY *pre = *head;
		cellXY *nxt = (*head)->next;
        while(nxt){
        	if(nxt->X == X && nxt->Y == Y){
        		pre->next = nxt->next;
                if(pre->next){
                	pre->next->prev = pre;
                }
                free(nxt);
        	}
        	pre = nxt;
        	nxt = nxt->next;
        }

	}
	cleanCoin(X,Y);
}


unsigned int getCoins(unsigned short int x, unsigned short int y, cellXY **head, cellXY **tail, cell ***stage){
	short int Ax0 = (short int)x;
	short int Ay0 = (short int)y;
	short int Ax1 = (short int)x+25;
	short int Ay1 = (short int)y+25;

	if((*stage)[Ax0/32][Ay0/32].type==6){(*stage)[Ax0/32][Ay0/32].type = 0;deleteCoins(Ax0/32, Ay0/32, head, tail, stage);return 1;}
	if((*stage)[Ax0/32][Ay1/32].type==6){(*stage)[Ax0/32][Ay1/32].type = 0;deleteCoins(Ax0/32, Ay1/32, head, tail, stage);return 1;}
	if((*stage)[Ax1/32][Ay0/32].type==6){(*stage)[Ax1/32][Ay0/32].type = 0;deleteCoins(Ax1/32, Ay0/32, head, tail, stage);return 1;}
	if((*stage)[Ax1/32][Ay1/32].type==6){(*stage)[Ax1/32][Ay1/32].type = 0;deleteCoins(Ax1/32, Ay1/32, head, tail, stage);return 1;}
	return 0;
}

void UpdateCoins(cellXY **head, cellXY **tail, cell***stage){
	if(*head == NULL){return;}
	//printf("Seem the coin list is not empty\n");
	cellXY *temp = *head;
	while(temp!=NULL){
		unsigned short int X = temp->X;
		unsigned short int Y = temp->Y;
		if((*stage)[X][Y].ptr->counter%10!=0){
			temp = temp->next;
			(*stage)[X][Y].ptr->counter++;
			continue;
		}
		cleanCoin(X,Y);
		drawCoin(X, Y, ((*stage)[X][Y]).ptr);
		temp = temp->next;
	}
}
