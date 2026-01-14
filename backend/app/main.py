from fastapi import FastAPI
from fastapi.responses import JSONResponse
from pydantic import BaseModel

app = FastAPI()

class JoystickInput(BaseModel):
    device_id: str
    x: float
    y: float
    button: bool
    timestamp: int

@app.get("/")
def read_root():
    return {"TODO": "Returns current game state"}

@app.post("/data")
def receive_data(data: JoystickInput):
    return JSONResponse(content={"status": "Data received"})
