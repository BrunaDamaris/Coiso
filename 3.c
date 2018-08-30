#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ITEM element;
typedef struct HASH hash_table;

struct ITEM
{
	int key;
	int value;
	element* next;
};

struct HASH
{
	int lenght;
	element *table[1000000];
};
int max,compadd,comphas,compdel;
hash_table* create_hash()
{
	hash_table* new_hash = (hash_table*) malloc(sizeof(hash_table));
	new_hash->lenght = 0;
	int i;
	for(i = 0; i < max;i++)
	{
		new_hash->table[i] = NULL;
	}
	return new_hash;
}
int put2(hash_table *ht,int key,int value)
{
	int k = key % max;
	if(ht->table[k] == NULL)
	{
		element *new_element = (element*) malloc(sizeof(element));
		new_element->key = key;
		new_element->value = value;
		new_element->next = NULL;
		ht->table[k] = new_element;
		ht->lenght++;
		return 1;
	}
	else if(ht->table[k] != NULL)
	{
		if(ht->table[k]->next != NULL)
		{
			element* temp = ht->table[k]->next;
			while(temp != NULL)
			{
				temp = temp->next;
				compadd++;
				if(temp->value == value)
				{
					return 0;
				}
			}
		}
		else
		{
			compadd++;	
			if(ht->table[k]->value == value)
			{
				return 0;
			}
		}
		element *new_element = (element*) malloc(sizeof(element));
		new_element->key = key;
		new_element->value = value;
		new_element->next = ht->table[k];
        ht->table[k] = new_element;
        ht->lenght++;
    }
    return 1;
}
int get(hash_table *ht,int key)
{
	int k = key % max;
	if(ht->table[k] != NULL)
	{
		if(ht->table[k]->next != NULL)
		{
			element* temp = ht->table[k]->next;
			while(temp != NULL)
			{
				temp = temp->next;
				comphas++;
				if(temp->key == key)
				{
					return 1;
				}
			}
			return 0;
		}
		else{
			comphas++;
			if(ht->table[k]->key == key)
			{
				return 1;
			}
		}
	}
	return 0;
}

int removefrom(hash_table *ht,int key)
{
	int k = key % max;
	if(ht->table[k] != NULL)
	{
		if(ht->table[k]->next != NULL)
		{
			element* temp = ht->table[k]->next;
			while(temp != NULL)
			{
				temp = temp->next;
				if(temp->key == key)
				{
					compdel++;
					free(temp);
					ht->lenght--;
					return 1;
				}
			}
			return 0;
		}
		else{
			compdel++;
			if(ht->table[k]->key == key)
			{
				ht->lenght--;
				return 1;
			}
		}
		k = (k+1) % max;
	}
	return 0;
}
void print_hash(hash_table *ht)
{
	int i=0;
	while(i < max)
	{
		if(ht->table[i] != NULL)
		{
			printf("%d -> ",i);
			printf("%d -> ",ht->table[i]->value);
			if(ht->table[i]->next != NULL)
			{
				while(ht->table[i]->next != NULL)
				{	
					printf("%d -> ",ht->table[i]->next->value);
					ht->table[i]->next = ht->table[i]->next->next;
				}
				i++;
			}
			else{
				i++;
			}
			printf("\\\n");
		}
		else
		{
			printf("%d -> \\\n",i);
			i++;
		}
	}
}

void rehashing(hash_table* ht)
{
	hash_table* new_hash = create_hash();
	max = max*2 - 1;
	int i=0;
	while(ht != NULL)
	{
		while(ht->table[i] != NULL)
		{
			if(ht->table[i]->next != NULL)
			{
				while(ht->table[i]->next != NULL)
				{
					put2(new_hash,ht->table[i]->next,ht->table[i]->next);
					ht->table[i]->next = ht->table[i]->next->next;
				}
				i++;
			}
			else
			{
				i++;
			}
		}
		i++;
	}
}
int main(int argc, char const *argv[])
{
	hash_table* hash = create_hash();
	max = 7;
	int number,right,add = 0,has = 0,del = 0,cases = 0;
	char operations[1000];
	while(scanf("%s",operations) != EOF)
	{
		scanf("%d",&number);
		if(strcmp(operations,"ADD") == 0)
		{
			right  = put2(hash,number,number);
			if(right)
			{
				add = 1;
			}
			printf("%d %d %d\n",cases,add,compadd);
			add = 0;
			compadd = 0;
		}
		else if(strcmp(operations,"HAS") == 0)
		{
			right  = get(hash,number);
			if(right)
			{
				has = 1;
			}
			printf("%d %d %d\n",cases,has,comphas);
			has = 0;
			comphas = 0;
		}
		else if(strcmp(operations,"DEL") == 0)
		{
			right = removefrom(hash,number);
			if(right)
			{
				del = 1;
			}
			printf("%d %d %d\n",cases,del,compdel);
			del = 0;
			compdel = 0;
		}
		else if(strcmp(operations,"PRT") == 0)
		{
			printf("%d %d %d %d\n",cases,max,hash->lenght,0);
		}
		cases++;
	}
	return 0;
}