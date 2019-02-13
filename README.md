# 링 버퍼
## 📢 개요
  **링 버퍼**(Ring buffer)은 대게 원형 큐(환형 큐; Circular queue)를 의미한다. 
  
  실제로는 메모리상에서 선형 구조로 된 고정된 크기의 버퍼이지만, 양 끝이 연결된 것처럼 사용할 수 있게 해주는 자료 구조이다. 원형 버퍼를 이용하면 거의 성능 저하 없이 단순 배열을 덱처럼 사용할 수 있다.

## 🅿 원리

  원형 버퍼는 먼저 비어 있고 고정된 크기로 시작한다. 다음은 크기가 7인 원형 버퍼에서의 입출력 예제이다.

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
