from telegram import Update
from telegram.ext import (
    ApplicationBuilder, CommandHandler, ContextTypes, MessageHandler, filters
)

with open('.token') as f:
    token = f.read().strip()

async def hello(update: Update, context: ContextTypes.DEFAULT_TYPE) -> None:
    await update.message.reply_text(f'Hello {update.effective_user.first_name}')

async def game_command(update: Update, context: ContextTypes.DEFAULT_TYPE) -> None:
    await update.message.reply_text(f'Hello {update.effective_user.first_name}')


def main():

    app = ApplicationBuilder().token(token).build()

    app.add_handler(CommandHandler("hello", hello))
    app.add_handler(MessageHandler(filters.ALL, game_command))

    app.run_polling()


if __name__ == '__main__':
    main()
