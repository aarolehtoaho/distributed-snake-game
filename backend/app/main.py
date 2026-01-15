import asyncio
from contextlib import asynccontextmanager
from fastapi import FastAPI
from fastapi.responses import JSONResponse
from pydantic import BaseModel
from app.config import GAME_SPEED

from app.game.game import Game

game = Game()

async def game_loop():
    while True:
        game.update()
        await asyncio.sleep(1.0 / GAME_SPEED)

@asynccontextmanager
async def lifespan(_: FastAPI):
    game_task = asyncio.create_task(game_loop())
    yield
    game_task.cancel()

app = FastAPI(lifespan=lifespan)

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
