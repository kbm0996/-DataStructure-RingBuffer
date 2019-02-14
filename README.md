# 링 버퍼
## 📢 개요
 **링 버퍼**(Ring buffer)은 원형 큐(환형 큐; Circular queue), 순환 큐, 순환 버퍼라고도 부른다. 이는 메모리상에서 큐(Queue)의 헤드(Head)를 나타내는 포인터와 꼬리(Tail)를 나타내는 포인터가 있는 선형 구조로 된 고정 길이 배열이지만, 논리적으로 양 끝이 연결된 것처럼 사용할 수 있어 계속해서 순환하여 사용할 수 있는 자료 구조다. 
  
 원형 버퍼의 가장 큰 특징은 고정 크기이지만 입력한 데이터를 제때에 출력만 해준다면 오래된 데이터가 자동으로 무효화되기 때문에 거의 성능 저하 없이 단순 배열을 덱처럼 사용할 수 있다는 점이다. 덕분에 재사용이 가능하여 메모리를 절약할 수 있다. 하지만, 버퍼의 크기를 초과하는 데이터를 입력하거나 입력된 데이터보다 더 많이 출력할 경우에는 데이터가 짤려서 입력된다던지 엉뚱한 데이터가 출력된다던지 다양한 문제가 발생할 수도 있다. 해당 문제는 프로그래밍 중에 안전 장치를 마련하기 보다는 제대로 된 모듈화를 위해서 대게 사용자의 책임에 맡기는 편이다. 단, 버퍼의 시작과 끝뿐만 아니라 가운데에서 요소를 추가하고 제거해야하는 큐의 경우에는 링크드 리스트로 구현하는 것이 좋다.
  
 데이터를 입력할 때 "FIFO"(first in first-out) 방식으로 꼬리 포인터에서부터 추가된다. 데이터를 출력할 경우엔 추가된 순서대로 헤드 포인터에서부터 제거된다. 또한 요소가 추가되고 제거 될 때 두 포인터가 모두 이동한다. 때문에 헤드 포인터와 버퍼 포인터가 달라 헤드 포인터는 배열의 첫 번째 요소를 가리키지 않는다.
  
 링 버퍼는 일반적으로 네트워크 프로그램과 같이 입출력이 서로 다른 속도로 발생하는 경우에 사용된다. 예를  입출력이 지연된 데이터를 폐기하는 대신 데이터가 링 버퍼에 기록 된 다음 네트워크를 다시 사용할 수 있게 되면 보내지도록 구현할 수 있다. 
  
  
## 🅿 원리

  원형 버퍼는 비어 있고 고정된 크기로 시작한다. 다음은 크기가 7인 원형 버퍼에서의 입출력 예제이다.

  ![capture](https://github.com/kbm0996/RingBuffer/blob/master/figure/1.png)
  
   **figure 1. Phase 1*
   
  빈 원형 버퍼에 다음과 같이 1이 입력되었다고 하자 (정확한 시작 위치는 원형 버퍼에서는 중요치 않다)

  ![capture](https://github.com/kbm0996/RingBuffer/blob/master/figure/2.png)
  
  **figure 2. Phase 2*
   
  그리고 2와 3이 추가로 입력되면 다음과 같이 3개의 원소를 갖게 된다.

  ![capture](https://github.com/kbm0996/RingBuffer/blob/master/figure/3.png)
  
  **figure 3. Phase 3*
   
  이 중 두 개의 원소가 출력되면 1과 2가 사라지고 3이 남게 된다

  ![capture](https://github.com/kbm0996/RingBuffer/blob/master/figure/4.png)
  
  **figure 4. Phase 4*
   
  이 버퍼의 크기는 7이므로 7개의 원소가 입력되면 꽉 차게 된다

  ![capture](https://github.com/kbm0996/RingBuffer/blob/master/figure/5.png)
  
  **figure 5. Phase 5*

  ![capture](https://github.com/kbm0996/RingBuffer/blob/master/figure/400px-Circular_Buffer_Animation.gif)
  
  **figure 6. Circular Buffer (animated gif)*
  
  
 ## 📌 이미지 및 설명 출처 
 
 원리 파트 - https://en.wikipedia.org/wiki/Circular_buffer
