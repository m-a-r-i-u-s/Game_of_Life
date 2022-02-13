
import ScreenSaver

class SaveMyLife: ScreenSaverView {

    // MARK: - Initialization
    private var universe = Array(repeating: Array(repeating: 0, count: 200), count: 200)
    private var parallel_universe = Array(repeating: Array(repeating: 0, count: 200), count: 200)
    
    override init?(frame: NSRect, isPreview: Bool) {
        super.init(frame: frame, isPreview: isPreview)
        makeBigBang()

        
      }

    @available(*, unavailable)
    required init?(coder decoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    // MARK: - Lifecycle

    override func draw(_ rect: NSRect) {
        drawBackground(.darkGray)
        drawGrid()
        makeCycle()
        drawUniverse()

    }

    override func animateOneFrame() {
        super.animateOneFrame()
        
        
        makeCopy()
        
        setNeedsDisplay(bounds)
    }

    // MARK: - Helper Functions
    
    private func mod(_ a: Int, _ b: Int) -> Int {
        let out: Int
        if ( a < 0 ) {out = a % b + b}
        else  {out = a % b}
        return out
    }
    
    private func makeCopy() {
        for (i, row) in self.universe.enumerated(){
            for (j, _) in row.enumerated(){
                
                self.universe[i][j] = self.parallel_universe[i][j]
            }
            
        }
        
    }
    
    private func makeCycle() {
        
        var sum: Int

        
        for (i, row) in self.universe.enumerated(){
            for (j, _) in row.enumerated(){
                
                sum = 0
                
                for m in i-1...i+1 {
                    for k in j-1...j+1 {
                        if !(m == i && k == j) {sum += self.universe[mod(m, 200)][mod(k, 200)]}
                    }
                }

                if self.universe[i][j] == 1 {
                    if ( sum > 3 || sum < 2) { self.parallel_universe[i][j] = 0 }
                    else { self.parallel_universe[i][j] = 1 }
                }
                else {
                    if (sum == 3) { self.parallel_universe[i][j] = 1 }
                    else { self.parallel_universe[i][j] = 0}
                }
                
        
            }
        }
    }
    
    private func drawUniverse() { //}(_ universe: [[Int]]){
        
        for (i, row) in self.universe.enumerated(){
            for (j, col) in row.enumerated(){
                
                if col == 1 {
                    drawRect(0 + CGFloat(i) * 10 + 5, 0 + CGFloat(j) * 10 + 5)
//                    drawBall(0 + CGFloat(i) * 10 + 5, 0 + CGFloat(j) * 10 + 5, 2.5)
                }
            }
        }
        
    }
    
    private func makeBigBang(){

        var draw_ran: Int
        
        for (i, row) in self.universe.enumerated(){
            for (j, _) in row.enumerated(){
                
                draw_ran = Int.random(in: 1..<101)
                
                if draw_ran < 25 {
                    self.universe[i][j] += 1
                }
            }
        }
        
        
    }
    
    private func drawBackground(_ color: NSColor) {
        let background = NSBezierPath(rect: bounds)
        color.setFill()
        background.fill()
    }
    
    private func drawBall(_ x: Float64,_ y: Float64,_ r: Float64) {
        let ballRect = NSRect(x: x - r,
                              y: y - r,
                              width: r * 2,
                              height: r * 2)
        let ball = NSBezierPath(roundedRect: ballRect,
                                xRadius: r,
                                yRadius: r)
        NSColor.black.setFill()
        ball.fill()
    }
    
    private func drawRect(_ x: Float64,_ y: Float64) {
        let paddleRect = NSRect(x: x - 5 / 2,
                                y: y - 5 / 2,
                                width: 5,
                                height: 5)
        let paddle = NSBezierPath(rect: paddleRect)
        NSColor.systemOrange.setFill()
        paddle.fill()
    }
    
    private func drawGrid() {
        let gridPath = NSBezierPath()
        
        for i in 0...200{
            
            //Draw horizontal lines
            gridPath.move(to: CGPoint(x: 0, y: 0 + CGFloat(i) * 10))
            gridPath.line(to: CGPoint(x: 0 + CGFloat(200) * 10, y: 0 + CGFloat(i) * 10))
            
            //Draw vertical lines
            gridPath.move(to: CGPoint(x: 0 + CGFloat(i) * 10, y: 0 ))
            gridPath.line(to: CGPoint(x: 0 + CGFloat(i) * 10, y: 0 + CGFloat(200) * 10))
            
            
        }
        
        gridPath.stroke()
    }

 
}
