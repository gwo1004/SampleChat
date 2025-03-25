## Project 09 - SampleChat

### Dependency (Build.cs)
  - UMG : 언리얼 UUserWIdget 관련 UMG 모듈추가
  - Netcore : 언리얼 RPC 및 Server-Client통신 관련 모듈 추가
    - PlayerState 내 Replicated를 사용한 동기화를 위한 DOREPLIFETIME 관련 모듈
  - Slate / SlateCore : 언리얼 IMGUI기반의 구현되어있는 UI 관련 모듈
    - ETextCommit::Type 관련 모듈

### 영상

[Sparta Project 09]([Chat Listen Server](https://www.youtube.com/watch?v=5jxAF4k9qf4))

### PlayerController
  - Server : 클라이언트(유저)와 Network를 통한 통신을 하기위한 객체
  - Client : 유저의 입력을 받아 그와 관련된 로직을 처리하며, 해당 입력들을 통해 서버와 통신
    - 대역폭을 고려하여 서버에서는 사운드/비주얼같은 렌더링 처리를 하지않음.
    - UI의 입력들을 받아 서버에게 전송하는것과 같은 본인 로컬에서만 실행시
  - Server에서 생성되며, 유저들은 자신의 로컬 내 해당 컨트롤러가 복제되는 구조
  - HasAuthority() : 권한을 가지고 있는지. 즉, 서버에서 실행되고있는지에 대한 Bool 리턴.
  - IsLocalController() : 유저의 로컬 클라이언트 내 컨트롤러인지에 대한 Bool 리턴.
    
### PlayerState
  - Player간 데이터들을 저장하는 클래스
  - 각각의 Player마다 다른 데이터 값을 보유할 수 있으며, Replicated를 통한 서버-클라이언트간 데이터 값 동기화 가능
  - Replicated : Server-Client간 데이터 동기화
  - ReplicatedUsing = OnRep_Signature : 해당 데이터 변경시, 바인딩된 이벤트 콜백
    - OnRep : 언리얼 컨벤션. 해당 컨벤션을 통해 Replicated시 언리얼에서 내부적으로 바인딩, 콜백
  - GetLifetimeReplicatedProps() : 리플리케이션 등록 작업을 수행하는 함수
  - DOREPLIFETIME(MyClass, MyVar) : 언리얼에게 해당 변수를 네트워크로 복제 명령을 내리는 매크로. 
  - FLifetimeProperty : 언리얼에서 복제할 변수들의 리스트. DOREPLIFETIME_... 관련 매크로로 추가한 변수의 정보 저장

### PlayerState VS GameState
  - 리플리케이션 적용 가능, 서버 -> 클라이언트에게 복제
  - 언리얼 내 Replication 관련 기능 지원
  
  - Player State
    - 플레이어 개별 상태 저장, 각 Controller마다 1개씩 생성
    - 로컬 본인 외 다른 PlayerState 접근 가능
    - Player마다 다른 난수를 저장하고 싶을 경우
  - Game State
    - 게임 전체의 상태 저장, 게임당 1개 생성
    - 게임 전체적인 상태를 관리, 유저들이 공유받는 공유 객체
    - 난수 생성 시 모든 클라이언트들이 동일값의 난수 저장시

<details>
  <summary> 관련 학습 TIL 작성 링크</summary>
  https://mynameiskgws.tistory.com/38
  https://mynameiskgws.tistory.com/60
  https://mynameiskgws.tistory.com/64
  https://mynameiskgws.tistory.com/65
</details>
