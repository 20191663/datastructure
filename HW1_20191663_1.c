#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Insert(char*, char, int);

int main(){
	char str[1000];
	scanf("%s",str);
	
	int *l, *m, *s;	//large:[], medium:{}, small:()
	int num_l=0, num_m=0, num_s=0, i, j=0;
	l = (int*)malloc(sizeof(int)*num_l);
	m = (int*)malloc(sizeof(int)*num_m);
	s = (int*)malloc(sizeof(int)*num_s);

	for(i=0;str[i]!='\0';i++){
		if(strchr("[]{}()",str[i])==NULL){
			continue;
		}
		else if(str[i]=='['){
			num_l++;
			l = realloc(l, sizeof(int)*num_l);
			l[num_l-1] = i;
		}
		else if(str[i]=='{'){
			num_m++;
			m = realloc(m, sizeof(int)*num_m);
			m[num_m-1] = i;
		}
		else if(str[i]=='('){
			num_s++;
			s = realloc(s, sizeof(int)*num_s);
			s[num_s-1] = i;
		}
		else if(str[i]==']'){
			if(num_l==0){
				Insert(str, '[', i);
				i++;
				j++;
			}
			else{
				num_l--;
				if(num_m>0 && num_s>0){
					while(1){
						if(m[num_m-1]>l[num_l] && m[num_m-1]>s[num_s-1]){
							Insert(str, '}', m[num_m-1]+1);
							num_m--;
							i++;
							j++;
						}
						else if(s[num_s-1]>l[num_l] && s[num_s-1]>m[num_m-1]){
							Insert(str, ')', s[num_s-1]+1);
							num_s--;
							i++;
							j++;
						}
						else
							break;
					}
				}
				if(num_m>0){
					while(m[num_m-1]>l[num_l]){
						Insert(str, '}', m[num_m-1]+1);
						num_m--;
						i++;
						j++;
					}
				}
				if(num_s>0){
					while(s[num_s-1]>l[num_l]){
						Insert(str, ')', s[num_s-1]+1);
						num_s--;
						i++;
						j++;
					}
				}
			}
		}
		else if(str[i]=='}'){
			if(num_m==0){
				Insert(str, '{', i);
				i++;
				j++;
			}
			else{
				num_m--;
				if(num_l>0 && num_s>0){
					while(1){
						if(l[num_l-1]>m[num_m] && l[num_l-1]>s[num_s-1]){
							Insert(str, ']', l[num_l-1]+1);
							num_l--;
							i++;
							j++;
						}
						else if(s[num_s-1]>m[num_m] && s[num_s-1]>l[num_l-1]){
							Insert(str, ')', s[num_s-1]+1);
							num_s--;
							i++;
							j++;
						}
						else
							break;
					}
				}
				if(num_l>0){
					while(l[num_l-1]>m[num_m]){
						Insert(str, ']', l[num_l-1]+1);
						num_l--;
						i++;
						j++;
					}
				}
				if(num_s>0){
					while(s[num_s-1]>m[num_m]){
						Insert(str, ')', s[num_s-1]+1);
						num_s--;
						i++;
						j++;
					}
				}
			}
		}
		else if(str[i]==')'){
			if(num_s==0){
				Insert(str, '(', i);
				i++;
				j++;
			}
			else{
				num_s--;
				if(num_l>0 && num_m>0){
                    while(1){
                        if(l[num_l-1]>s[num_s] && l[num_l-1]>m[num_m-1]){
                            Insert(str, ']', l[num_l-1]+1);
                            num_l--;
                            i++;
                            j++;
                        }
                        else if(m[num_m-1]>s[num_s] && m[num_m-1]>l[num_l-1]){
                            Insert(str, '}', m[num_m-1]+1);
                            num_m--;
                            i++;
                            j++;
                        }
                        else
                            break;
                    }
                }			
				if(num_m>0){
					while(m[num_m-1]>s[num_s]){
						Insert(str, '}', m[num_m-1]+1);
						num_m--;
						i++;
						j++;
					}
				}
				if(num_l>0){
					while(l[num_l-1]>s[num_s]){
						Insert(str, ']', l[num_l-1]+1);
						num_l--;
						i++;
						j++;
					}
				}
			}
		}
	}
 	while(num_l>0){
		num_l--;
		Insert(str, ']', l[num_l]+1);
		j++;
	}
	while(num_m>0){
		num_m--;
		Insert(str, '}', m[num_m]+1);
		j++;
	}
	while(num_s>0){
		num_s--;
		Insert(str, ')', s[num_s]+1);
		j++;
	}
	if(j==0){
		printf("well formed string\n");
	}
	else{
		printf("not well formed string\n추가되는 괄호 수: %d\n%s\n",j,str);
	}

	free(l);
	free(m);
	free(s);

	return 0;
}

void Insert(char* str, char c, int i){
	int j, loc = strlen(str);
	str[loc+1]='\0';
	for(j=loc;j>i;j--){
		str[j]=str[j-1];
	}
	str[j] = c;
}
