from fastapi import FastAPI
from fastapi.responses import JSONResponse
from pydantic import BaseModel

from app.game.game import Game

app = FastAPI()

game = Game()
class JoystickInput(BaseModel):
    device_id: str
    x: float
    y: float
    button: bool
    timestamp: int

@app.get("/")
def read_root():
    return game.get_state()

@app.post("/data")
def receive_data(data: JoystickInput):
    game.set_input(data.x, data.y, data.button, data.timestamp)
    return JSONResponse(content={"status": "input received"})
