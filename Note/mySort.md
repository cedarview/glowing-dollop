```java
    public void inserSort(int arry[]){
        inserSort(arry,1);
    }

    public void inserSort(int arry[],int end){
        int tmp=0;
        if(end>=1&&end<arry.length) {
            for (int i = end; i > 0; i--) {
                if (arry[i] < arry[i - 1]) {
                    tmp = arry[i];
                    arry[i] = arry[i-1];
                    arry[i-1]= tmp;
                } else {
                    break;
                }
            }
            inserSort(arry,end+1);
        }
    }

    public void chooseSort(int arry[]){
        for(int i=0;i<arry.length;i++){
            int tmp = i;
            for(int j=i;j<arry.length;j++){
                if(arry[j]<arry[tmp]){
                    tmp = j;
                }
            }
            if(i != tmp) {
                int tmpNum = arry[tmp];
                arry[tmp] = arry[i];
                arry[i] = tmpNum;
            }
        }
    }

    public void bubbleSort(int arry[]){
        bubbleSort(arry,arry.length-1);
    }

    public void bubbleSort(int arry[],int end){
        if(end>=1){
            boolean swap = false;
            for(int i=0;i<end;i++){
                if(arry[i]>arry[i+1]){
                    int tmp =arry[i];
                    arry[i] = arry[i+1];
                    arry[i+1]=tmp;
                    swap = true;
                }
            }
            if(swap){
                bubbleSort(arry,end-1);
            }
        }
    }


    public void qSort(int array[]){
        qSort(array,0,array.length-1);
    }

    public void qSort(int array[],int left,int right){
        if(left<right){
            int pivot = array[left];
            int i=0;
            int j=left+1;
            while (j<=right) {
                while (array[j] > pivot) {
                    j++;
                }
                int tmp =array[i+1];
                array[i+1] = array[j];
                array[j]=tmp;
                i++;
                j++;
            }

            array[left]=array[i];
            array[i]=pivot;

            qSort(array,left,i-1);
            qSort(array,i+1,right);

        }
    }

    public void qSort1(int array[],int left,int right){

        if(left<right) {
            int pivot = array[left];
            int i = left;
            int j = right;

            while (i < j) {
                while (i < j && array[j] >= pivot) {
                    j--;
                }

                array[i] = array[j];

                while (i < j && array[i] <= pivot) {
                    i++;
                }
                array[j] = array[i];
            }
            array[i]=pivot;
            qSort(array,left,i-1);
            qSort(array,i+1,right);
        }
    }

    public void qSort2(int array[],int low,int high){

        int l = low;
        int h = high;
        int base = array[low];
        while (l<h) {

            while (h > l && array[h] >= base) {
                h--;
            }
            if(l<h) {
                //int tmp = 0;
                //tmp = array[l];
                array[l] = array[h];
                array[h] = base;
                l++;
            }

            while (h > l && array[l] <= base) {
                l++;
            }
            if(l<h) {
                //int tmp = 0;
                array[h] = array[l];
                array[l] = base;
                //array[h] = tmp;
                h--;
            }
        }

        if(l>low)
            qSort(array,low,l-1);
        if(h<high)
            qSort(array,l+1,high);
    }
```
