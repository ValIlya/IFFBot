from telegram import Update
from telegram.ext import (
    ApplicationBuilder,
    CommandHandler,
    ContextTypes,
    MessageHandler,
    filters,
)
from deep_translator import GoogleTranslator


from iffbot.storage import Storage

with open(".token") as f:
    token = f.read().strip()

storage = Storage()


async def start(update: Update, context: ContextTypes.DEFAULT_TYPE) -> None:
    info = storage.get_user_info(context._chat_id)
    if info.story.is_running():
        return
    message = await info.story.start()
    translated = GoogleTranslator(source="en", target=info.language).translate(message)
    await update.message.reply_text(translated)


async def game_command(update: Update, context: ContextTypes.DEFAULT_TYPE) -> None:
    try:
        info = storage.get_user_info(context._chat_id)
        message = await info.story.do(update.message.text)
        translated = GoogleTranslator(source="en", target=info.language).translate(
            message
        )
        await update.message.reply_text(translated)
    except:
        await start()


async def lang_command(update: Update, context: ContextTypes.DEFAULT_TYPE) -> None:
    info = storage.get_user_info(context._chat_id)
    lang = context.args[0]
    info.language = lang
    message = f"Set language to '{lang}'"
    translated = GoogleTranslator(source="en", target=lang).translate(message)
    await update.message.reply_text(translated)


def main():
    app = ApplicationBuilder().token(token).build()

    app.add_handler(CommandHandler("start", start))
    app.add_handler(CommandHandler("lang", lang_command))
    app.add_handler(MessageHandler(filters.ALL, game_command))

    app.run_polling()


if __name__ == "__main__":
    main()
