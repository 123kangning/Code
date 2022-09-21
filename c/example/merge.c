
L* merge1(L* la,L* lb){
    L* lc=la,*head=lc;
    la=la->next;
    for(;la->next!=NULL&&lb->next!=NULL;la=la->next,lb=lb->next){
        lc->next=la;
        lc=lc->next;
        lc->next=lb;
        lc=lc->next;
    }
    while(lb!=NULL){
        lc->next=lb;
        lc=lc->next;
    }
    return head;
}
L* merge2(L* la,L* lb){
    L* lc=lb,*head=lc;
    lb=lb->next;
    for(;la->next!=NULL&&lb->next!=NULL;la=la->next,lb=lb->next){
        lc->next=la;
        lc=lc->next;
        lc->next=lb;
        lc=lc->next;
    }
    while(la!=NULL){
        lc->next=la;
        lc=lc->next;
    }
    return head;
}